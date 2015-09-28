#include "SP_APPROX.h"

void SP_APPROX::initialize(Parser& parser)
{
    
    n = parser.sequences[0].size()+1;
    this->parser = &parser;
    k = parser.sequences.size();
    M_size = 0;
    gap = -1;   
 
}
void SP_APPROX::compute_S() {
    
    int i,j;
    S.clear();
    S.resize(n, vector<int64_t>(n, 0));
    
    for(i=1;i<n;i++)
        S[0][i] = S[0][i-1] + parser->gap_cost;

    for(i=1;i<n;i++)
        S[i][0] = S[i-1][0] + parser->gap_cost;

    for(i=1;i<n;i++){
       
        for(j=1;j<n;j++){
                int64_t v1 = S[i-1][j-1]+parser->score[parser->sequences[x][i-1]][parser->sequences[y][j-1]];
                int64_t v2 = S[i][j-1]+parser->gap_cost;
                int64_t v3 = S[i-1][j]+parser->gap_cost;
                S[i][j] = min(v1,min(v2,v3));
        }
        
    }
    
}



void SP_APPROX::find_two_alignment_helper(int i, int j){
    
    if(i>0 && j>0){
        
        if(S[i][j] == S[i-1][j-1]+parser->score[parser->sequences[x][i-1]][parser->sequences[y][j-1]]){
            find_two_alignment_helper(i-1,j-1);
            two_alignment.push_back(parser->sequences[x][i-1]);
            two_alignment.push_back(parser->sequences[y][j-1]);
        }
        else if(S[i][j] == S[i][j-1]+parser->gap_cost){
            find_two_alignment_helper(i,j-1);
            two_alignment.push_back('-');
            two_alignment.push_back(parser->sequences[y][j-1]);
        }
        else if(S[i][j] == S[i-1][j]+parser->gap_cost){
            find_two_alignment_helper(i-1,j);
            two_alignment.push_back(parser->sequences[x][i-1]);
            two_alignment.push_back('-');
        }
    }
    else if(i == 0 && j > 0){
            while(j > 0){
                two_alignment.push_back('-');
                two_alignment.push_back(parser->sequences[y][j-1]);
                j--;
            }
    }
    else if(j == 0 && i>0){
            while(i>0){
                two_alignment.push_back(parser->sequences[x][i-1]);
                two_alignment.push_back('-');
                i--;
            }
    }
    return;
    
}

void SP_APPROX::find_two_alignment()
{
    
    compute_S();
    two_alignment.clear();
    find_two_alignment_helper(n-1,n-1);
    
}

void SP_APPROX::updateM()
{
    size_t i1; //index to first alignment in A
    list<char>::iterator ps1; //pointer to S1 in M (basically an iterator)
    ps1 = M[0].begin();
    size_t counter = 0; //Let t1 be the last time you inserted a gap column. Let t2 be the time you realize you ll need to insert a new gap column. This counter keeps track of the difference t2-t1. 
    //the idea is you have an iterator for every alignment in M, if you need to add a gap column, you move all the iterators towards the point of insertion, you insert the new column and then keep
    //the iterators in that position. The second time you ll have to create a new gap column by knowing t2-t1 you know how much you need to move your pointers to reach the position of insertion. In
    //this way we can guarantee O(n) total time per every alignment in M to insert all the necessary gaps
    i1 = 0;
    //initialize iterators
    M_size+=1;
    vector<list<char>::iterator> iters(M_size);
    M[M_size-1].resize(M[0].size(), '*');
    for(size_t d=0;d<M_size;d++) iters[d] = M[d].begin();
    list<char>::iterator pnew = M[M_size-1].begin();//pointer to new alignment in M, the one we are about to add
    while(ps1!=M[0].end() && i1<two_alignment.size()){
        if(*ps1 != '-' && two_alignment[i1]!='-'){
            ps1++;
            counter++;
            *pnew = two_alignment[i1+1];
            pnew++;
            i1 += 2;
        }
        else{
            if(*ps1 == '-'){
                ps1++;
                counter++;
                *pnew = '-';
                pnew++;
            }
            else if(two_alignment[i1] == '-'){
                //add space column to M
                //make every iterator point to the same position as i in M
                size_t a,b;
                for(a=0;a<M_size;a++){
                    for(b=0;b<counter;b++){
                        iters[a]++;
                    }
                    M[a].insert(iters[a], '-');
                }
                pnew--;
                *pnew = two_alignment[i1+1];
                pnew++;
                i1 = i1 + 2;
                counter = 0;
            }
        }
    }
}

void SP_APPROX::compute_D()
{
    
    size_t i,j;
    
    /*
     * find some sequence Sc such that D(Sc,Sj) for all j!=c is minimized
     */
    int64_t mnCost = inf;
    for(i=0;i<k;i++){ //O(k^2n^2)
        
        int64_t smCost = 0;
        for(j=0;j<k;j++){
        
            if(i!=j){
                x = i;
                y = j;
                compute_S();
                smCost += S[n-1][n-1];
            }
                
        }

        if(smCost < mnCost){
            mnCost = smCost;
            S1 = i;
        }   
    
    }
    /*
     * add the center sequence to M and then for the remaining k-1 sequences add them one by one by following the update algorithm implemented in updateM()
     */
  
    //add the Sc(referred to by index S1) sequence to M
    M.clear();
    M.resize(k);
    for(i = 0; i < parser->sequences[S1].size(); i++)
        M[0].push_back(parser->sequences[S1][i]);
    M_size = 1;
    //add the remaining sequences
    for(i=0;i<k;i++){
    
        if(i!=S1){
        
            x = S1;
            y = i;
            find_two_alignment();
            updateM();
	    
        }
    
    }
    sp_score();
    cout<<"Score: "<<score<<endl;
    printM();
    
}

int64_t SP_APPROX::getScore()
{    
    return score;
}

void SP_APPROX::printM(){
    size_t i;
    for(i=0;i<M_size;i++){
        list<char>::iterator it = M[i].begin();
        cout<<i<<": ";
        while(it!=M[i].end()){
            if(*it == '-') cout<<"-";
            else cout<<parser->proteins[*it];
            it++;
        }
        cout<<endl;
    }
}
    
void SP_APPROX::print_two_alignment(){
    
    size_t i;
    for(i=0;i<two_alignment.size();i+=2)
        if(two_alignment[i]=='-') cout<<'-';
        else cout<<parser->proteins[two_alignment[i]];
        cout<<endl;
    for(i=1;i<two_alignment.size();i+=2)
        if(two_alignment[i]=='-') cout<<'-';
        else cout<<parser->proteins[two_alignment[i]];
	
}
    
void SP_APPROX::sp_score(){
	
    size_t i,j;
    score = 0;
    for(i=0;i<k;i++){
	
        for(j=i+1;j<k;j++){
	    
            list<char>::iterator iti, itj;
            iti = M[i].begin();
            itj = M[j].begin();
            while(iti!=M[i].end()){
		
                char i_char = *iti;
                char j_char = *itj;
		    
                if(i_char == '-' && j_char == '-');
                else if(i_char == '-' || j_char == '-')
                    score += parser->gap_cost;
                else
                    score += parser->score[i_char][j_char];
		iti++;
		itj++;
            }
	    
        }
	
    }
    
}

void SP_APPROX::print_alignments() {
    printM();
}
