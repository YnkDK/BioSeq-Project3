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

#ifndef BIOSEQ_PROJECT2_SP_APPROX_H
#define BIOSEQ_PROJECT2_SP_APPROX_H
#include "MSA.h"
#include <vector>
#include <list>
#define inf 9999999999999
using namespace std;

class SP_APPROX : public MSA {
    
private:
    
    /*
     * variables
     * 
     */
        
    vector<vector<int64_t>> S;
    vector<char> two_alignment; //stores alignment between two sequences
    int n;
    int64_t score;
    Parser* parser;
    int gap;
    size_t S1; //index to S1
    size_t x,y;//index to the two sequences being aligned
    size_t k; //number of sequences
    vector<list<char>> M; //stores M, use list since it is implemented as a doubly connected list (ie inserting at a specific position once found takes O(1) time)
    
    /*
     * functions
     * 
     */
    void find_two_alignment_helper(int i, int j);
    void find_two_alignment();
    void compute_S(); //finds optimal alignment score when aligning two sequences denoted by their indexes i and j
    
    
public:
    /*
     * read all the necessary information from the external files
     * 
     */
    void initialize(Parser& parser);
    
    /*
     * computes the approximation SP score
     */
    void compute_D();
        
    int64_t getScore();
    
};

#endif //BIOSEQ_PROJECT2_SP_APPROX_H
