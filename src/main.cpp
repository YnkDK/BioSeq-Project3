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
    std::cout << "HELLO WORLD" << std::endl;
    Parser parser("input/testseqs_200_3.fasta");
    SP_EXACT_3 sp_ex;
    //sp_ex.initialize(parser);
    cout<<parser.gap_cost<<endl;
    sp_ex.initialize(parser);
    sp_ex.compute_D();
    cout<<sp_ex.getScore()<<endl;
    return EXIT_SUCCESS;
}