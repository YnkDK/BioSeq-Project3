/* -------------------------------------------------------------------------------------
** This software is implemented as part of the course
**     Algorithms in Bioinformatics - Sequences Q1/2015
** at Aarhus Univerity Denmark.
**
** MSA.h
** Interface/Abstract class for Multiple Sequence Alignment algorithms
**
** Author: Martin Storgaard, Konstantinos Mampentzidis and Henrik McQuoid Jespersen
** -----------------------------------------------------------------------------------*/

#ifndef BIOSEQ_PROJECT3_MSA_H
#define BIOSEQ_PROJECT3_MSA_H

class MSA {
public:

    /**
     * TODO: What should be initialized?
     * TODO: Define parameters
     */
    virtual void initialize() = 0;

    /**
     * Fill out the 3-dimensional cube D, such that D[n,n',n''] would be the optimal
     * or the best estimate hereof for any order of 3 sequences
     */
    virtual void compute_D() = 0;

    /**
     * Computes the score of current state
     */
    virtual int64_t getScore() = 0;


};

#endif //BIOSEQ_PROJECT3_MSA_H
