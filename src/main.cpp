/* -------------------------------------------------------------------------------------
** This software is implemented as part of the course
**     Algorithms in Bioinformatics - Sequences Q1/2015
** at Aarhus Univerity Denmark.
**
** main.cpp
** Main file
**
** Author: Martin Storgaard, Konstantinos Mampentzidis and Henrik McQuoid Jespersen
** -----------------------------------------------------------------------------------*/

#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <iostream> // cout, endl
#include "Parser.h"
#include "SP_EXACT_3.h"

int main(int argc, char** argv) {
    Parser parser("input/testseqs_10_3.fasta");
    SP_EXACT_3 sp_ex;
    sp_ex.initialize(parser);
    sp_ex.compute_D();
    cout<<"Optimal alignment cost: "<<sp_ex.getScore()<<endl;
    cout<<"Printing an alignment..."<<endl;
    sp_ex.find_alignment();
    cout<<"Verifying that the alignment matches the optimal cost..."<<endl;
    if(sp_ex.verify())
        cout<<"SUCCESS!!!"<<endl;
    else 
        cout<<"FAILURE!!!"<<endl;
    return EXIT_SUCCESS;
}