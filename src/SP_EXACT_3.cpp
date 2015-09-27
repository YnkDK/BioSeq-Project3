#include "SP_EXACT_3.h"

void SP_EXACT_3::initialize(Parser& parser)
{	
    D.clear();
    alignment.clear();
    n = parser.sequences[0].size()+1;
    D.resize(n, vector< vector<int64_t>>(n, vector<int64_t>(n, 0)));
    this->parser = &parser;
    gap = -1;	
 
}

void SP_EXACT_3::print_alignment(){
    if(alignment.size() == 0 || alignment.size()%3!=0) 
        cout<<"you are obviously doing something very wrong"<<endl;
    size_t i;
    for(i=0;i<alignment.size();i+=3)
        if(alignment[i] == '-') 
            cout<<'-';
        else
            cout<<parser->proteins[(int)alignment[i]];
    cout<<endl;
    for(i=1;i<alignment.size();i+=3)
        if(alignment[i] == '-') 
            cout<<'-';
        else
            cout<<parser->proteins[(int)alignment[i]];
    cout<<endl;
    for(i=2;i<alignment.size();i+=3)
        if(alignment[i] == '-') 
            cout<<'-';
        else
            cout<<parser->proteins[(int)alignment[i]];
    cout<<endl;
}

int64_t SP_EXACT_3::sp(int a, int b, int c)
{
    
    if(a!=gap && b!=gap && c!=gap)
        return parser->score[a][b] + parser->score[b][c] + parser->score[a][c];
    else if(a!=gap && b!=gap && c==gap)
        return parser->score[a][b]+parser->gap_cost*2;
    else if(a!=gap && b==gap && c!=gap)
        return parser->score[a][c] + parser->gap_cost*2;
    else if(a==gap && b!=gap && c!=gap)
        return parser->score[b][c]+parser->gap_cost*2;
    
    return 2*parser->gap_cost;
    
}

void SP_EXACT_3::compute_D()
{
    int i,j,k;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            for(k=0;k<n;k++){
                int64_t v0,v1,v2,v3,v4,v5,v6,v7;
                v0=v1=v2=v3=v4=v5=v6=v7=inf;
                if(i==0 && j==0 && k==0)
                    v0 = 0;
                if(i>0 && j>0 && k>0)
                    v1 = D[i-1][j-1][k-1] + sp(parser->sequences[0][i-1], parser->sequences[1][j-1], parser->sequences[2][k-1]);
                if(i>0 && j>0 && k>=0)
                    v2 = D[i-1][j-1][k] + sp(parser->sequences[0][i-1], parser->sequences[1][j-1], gap);
                if(i>0 && j>=0 && k>0)
                    v3 = D[i-1][j][k-1]+sp(parser->sequences[0][i-1],gap,parser->sequences[2][k-1]);
                if(i>=0 && j>0 && k>0)
                    v4 = D[i][j-1][k-1] + sp(gap,parser->sequences[1][j-1],parser->sequences[2][k-1]);
                if(i>0 && j>=0 && k>=0)
                    v5 = D[i-1][j][k] + sp(parser->sequences[0][i-1],gap,gap);
                if(i>=0 && j>0 && k>=0)
                    v6 = D[i][j-1][k] + sp(gap,parser->sequences[1][j-1],gap);
                if(i>=0 && j>=0 && k>0)
                    v7 = D[i][j][k-1] + sp(gap, gap, parser->sequences[2][k-1]);
                D[i][j][k] = min(v0,min(v1,min(v2,min(v3,min(v4,min(v5,min(v6,v7)))))));
            }
       }
    }
    
    score = D[n-1][n-1][n-1];
        
}



void SP_EXACT_3::find_alignment_helper(int i, int j, int k){
    
    if(i>0 && j>0 && k>0 && D[i][j][k] == (D[i-1][j-1][k-1] + sp(parser->sequences[0][i-1], parser->sequences[1][j-1], parser->sequences[2][k-1]))){
        
        find_alignment_helper(i-1,j-1,k-1);
        alignment.push_back(parser->sequences[0][i-1]);
        alignment.push_back(parser->sequences[1][j-1]);
        alignment.push_back(parser->sequences[2][k-1]);
        
    }
    else if(i>0 && j>0 && k>=0 && D[i][j][k] == (D[i-1][j-1][k] + sp(parser->sequences[0][i-1], parser->sequences[1][j-1], gap))){
        
        find_alignment_helper(i-1,j-1,k);
        alignment.push_back(parser->sequences[0][i-1]);
        alignment.push_back(parser->sequences[1][j-1]);
        alignment.push_back('-');
        
    }
    else if(i>0 && j>=0 && k>0 && D[i][j][k] == (D[i-1][j][k-1]+sp(parser->sequences[0][i-1],gap,parser->sequences[2][k-1]))){
        
        find_alignment_helper(i-1,j,k-1);
        alignment.push_back(parser->sequences[0][i-1]);
        alignment.push_back('-');
        alignment.push_back(parser->sequences[2][k-1]);
        
    }
    else if(i>=0 && j>0 && k>0 && D[i][j][k] == (D[i][j-1][k-1] + sp(gap,parser->sequences[1][j-1],parser->sequences[2][k-1]))){
        
        find_alignment_helper(i,j-1,k-1);
        alignment.push_back('-');
        alignment.push_back(parser->sequences[1][j-1]);
        alignment.push_back(parser->sequences[2][k-1]);
        
    
    }
    else if(i>0 && j>=0 && k>=0 && D[i][j][k] ==  (D[i-1][j][k] + sp(parser->sequences[0][i-1],gap,gap))){
        
        find_alignment_helper(i-1,j,k);
        alignment.push_back(parser->sequences[0][i-1]);
        alignment.push_back('-');
        alignment.push_back('-');
    
    }
    else if(i>=0 && j>0 && k>=0 && D[i][j][k] == (D[i][j-1][k] + sp(gap,parser->sequences[1][j-1],gap))){
        
        find_alignment_helper(i,j-1,k);
        alignment.push_back('-');
        alignment.push_back(parser->sequences[1][j-1]);
        alignment.push_back('-');
        
    }
    else if(i>=0 && j>=0 && k>0 && D[i][j][k] == (D[i][j][k-1] + sp(gap, gap, parser->sequences[2][k-1]))){
        
        find_alignment_helper(i,j,k-1);
        alignment.push_back('-');
        alignment.push_back('-');
        alignment.push_back(parser->sequences[2][k-1]);
        
    }
    
    
}

void SP_EXACT_3::find_alignment()
{
    find_alignment_helper(n-1,n-1,n-1);
    print_alignment();
    
}

int64_t SP_EXACT_3::getScore()
{    
    return score;
}

bool SP_EXACT_3::verify(){

    size_t i;
    int64_t alignment_score = 0;
    for(i=0;i<alignment.size();i+=3){
    
        int a,b,c;
        if(alignment[i] == '-') a = gap;
        else a = alignment[i];
        //cout<<parser->proteins[alignment[i]]<<" "<<parser->proteins[alignment[i+1]]<<" "<<parser->proteins[alignment[i+2]]<<endl;
        
        if(alignment[i+1] == '-') b = gap;
        else b = alignment[i+1];
        
        if(alignment[i+2] == '-') c = gap;
        else c = alignment[i+2];
        
        alignment_score += sp(a,b,c);
    
    }
    return alignment_score == getScore();
    
}