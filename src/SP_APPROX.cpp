#include "SP_APPROX.h"

void SP_APPROX::initialize(Parser& parser)
{
    
    n = parser.sequences[0].size()+1;
    this->parser = &parser;
    k = parser.sequences.size();
    gap = -1;   
 
}
void SP_APPROX::compute_S() {
    
    int i,j;
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
    find_two_alignment_helper(n-1,n-1);
    
}

void SP_APPROX::compute_D()
{
    
    size_t i,j;
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
    
    M.resize(k);
    for(i = 0; i < parser->sequences[S1].size(); i++)
        M[0].push_back(parser->sequences[S1][i]);
    
    vector<list<char>::iterator> its(k);
    its[0] = M.begin();
    
    for(i=0;i<k;i++){
    
        if(i!=S1){
        
            x = S1;
            y = i;
            find_two_alignment();
            
            
        
        }
    
    }
    
    
    
}

int64_t SP_APPROX::getScore()
{    
    return score;
}
