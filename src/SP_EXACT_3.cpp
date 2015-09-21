#include "SP_EXACT_3.h"

void GlobalAffine::initialize(Parser& )
{
	
	n = n + 1;
	D.resize(n, vector<int64_t>(n+1, vector<int64_t>(n)));
	parser = &Parser;
	gap = -1;
	
}



void GlobalAffine::compute_D()
{
	
	int i,j,k;
	for(i=0;i<n;i++){
	
		for(j=0;j<n;j++){
		
			for(k=0;k<n;k++){
			
				int64_t v0,v1,v2,v3,v4,v5,v6,v7;
				
				if(i==0 && j==0 && k==0)
					v0 = 0;
				
				if(i>0 && j>0 && k>0)
					v1 = D[i-1][j-1][k-1] + sp(parser->sequences[0][i], parser->sequences[1][j], parser->sequences[2][j]);
			
				if(i>0 && j>0 && k>=0)
					v2 = D[i-1][j-1][k] + sp(parser->sequences[0][i], parser->sequences[1][j], gap);
				
				if(i>0 && j>=0 && k>0)
					v3 = D[i-1][j][k-1]+sp(parser->sequences[0][i],gap,parser->sequences[2][k]);
				
				if(i>=0 && j>0 && k>0)
					v4 = D[i][j-1][k-1] + sp(gap,parser->sequences[1][j],parser->sequences[2][k]);
				
				if(i>0 && j>=0 && k>=0)
					v5 = D[i-1][j][k] + sp(parser->sequences[0][i],gap,gap);
				
				if(i>=0 && j>0 && k>=0)
					v6 = D[i][j-1][k] + sp(gap,parser->sequences[1][j],gap);
				
				if(i>=0 && j>=0 && k>0)
					v7 = D[i][j][k-1] + sp(gap, gap, parser->sequences[2][k]);
				
			}
			
			
		}
		
	}
	
	score = D[n-1][n-1][n-1];

}

int64_t GlobalAffine::getScore()
{
	
	return score;

}
