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

int main(int argc, char** argv) {
    std::cout << "HELLO WORLD" << std::endl;
    Parser("input/testseqs_10_3.fasta");
    return EXIT_SUCCESS;
}