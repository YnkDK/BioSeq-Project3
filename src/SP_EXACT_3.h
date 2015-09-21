/* -------------------------------------------------------------------------------------
** This software is implemented as part of the course
**     Algorithms in Bioinformatics - Sequences Q1/2015
** at Aarhus Univerity Denmark.
**
** global_affine.h
** Class implementing the functionalities of the global affine algorithm.
**
** Author: Martin Storgaard, Konstantinos Mampentzidis and Henrik McQuoid Jespersen
** -----------------------------------------------------------------------------------*/

#ifndef BIOSEQ_PROJECT2_GLOBAL_AFFINE_H
#define BIOSEQ_PROJECT2_GLOBAL_AFFINE_H
#include "MSA.h"
#include <vector>
using namespace std;

class GlobalAffine : public MSA {
    
private:
    
    /*
     * variables
     * 
     */
    
    vector<vector<vector<int64_t>>> D;
    int n;
	int64_t score;
	Parser* parser;
	int gap;
    
    /*
     * functions
     * 
     */
	
	int64_t sp(int a, int b, int c){
	
		if(a!=gap && b!=gap && c!=gap)
			return parser->score[a][b] + parser->score[b][c] + parser->score[a][c];
		else if(a!=gap && b!=gap && c==gap)
			return parser->score[a][b]+parser->gap_cost*2;
		else if(a!=gap && b==gap && c!=gap)
			return parser->score[a][c] + parser->gap_cost*2;
		else if(a==gap && b!=gap && c!=gap)
			return parser->score[b][c]+parser->gap_cost*2;
		else if(a!=gap && b==gap && c==gap)
			return 2*parser->gap_cost;
		else if(a==gap && b!=gap && c==gap)
			return 2*parser->gap_cost;
		else if(a==gap && b==gap && c!=gap)
			return 2*parser->gap_cost;
		
	}
	
    
    
public:
    /*
     * read all the necessary information from the external files
     * 
     */
    void initialize(Parser& parser);
    
    /*
     * compute the S matrix ( the cost matrix ) and return the number of optimal aligments
     */
    void compute_D();
	
    int64_t getScore();
     
};

#endif //BIOSEQ_PROJECT2_GLOBAL_AFFINE_H
