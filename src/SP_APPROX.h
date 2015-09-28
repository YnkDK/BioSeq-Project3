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
        
    vector<vector<int64_t>> S; //the cost matrix when trying to align two sequences
    vector<char> two_alignment; //stores alignment between two sequences
    int n;
    int64_t score;
    Parser* parser;
    int gap;
    size_t S1; //index to S1
    size_t x,y;//index to the two sequences being aligned
    size_t k; //number of sequences
    vector<list<char>> M; //stores M
    size_t M_size; //size of M
    
    /*
     * functions
     * 
     */
    void find_two_alignment_helper(int i, int j); //just a helper for find_two_alignment like in the second project
    void find_two_alignment(); //find alignment of two sequences after having computed S
    void compute_S(); //finds optimal alignment score when aligning two sequences denoted by their indexes i and j
    void updateM(); //extend M
    void printM(); //prints alignment of M
    void print_two_alignment(); //prints the two alignment stored in two_alignment
    void sp_score(); //finds the sp score of M
    
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

    void print_alignments();

    bool verify() {
        // The getScore function compute the score as we would verify it,
        // thus it does not make sense to do the same for verification
        return true;
    }
    
};

#endif //BIOSEQ_PROJECT2_SP_APPROX_H
