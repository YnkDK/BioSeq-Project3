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
#include <cstring> // cmpstr
#include "Parser.h"
#include "SP_EXACT_3.h"
#include "SP_APPROX.h"


void exec_func(MSA &alg, const char *func) {
    if (strcmp(func, "compute_d") == 0) {
        alg.compute_D();
        cout << "Computed D" << endl;
    } else if (strcmp(func, "print_score") == 0) {
        cout << "Optimal alignment cost: ";
        cout << alg.getScore() << endl;
    } else if (strcmp(func, "print_alignments") == 0) {
        cout << "Alignment found:" << endl;
        alg.print_alignments();
    } else if (strcmp(func, "verify") == 0) {
        if (alg.verify()) {
            cout << "The optimal cost found was verified succesfully" << endl;
        } else {
            cout << "The optimal cost found was NOT CORRECT!!" << endl;
        }
    }
}

void handle_sp_exact_3(SP_EXACT_3 sp_exact_3, int argc, char **argv) {
    cout << "#################" << endl;
    cout << "## SP_EXACT_3  ##" << endl;
    cout << "#################" << endl;


    cout << "Using FASTA file: " << argv[2] << endl;
    for (int i = 3; i < argc; i++) {
        exec_func(sp_exact_3, argv[i]);
    }
}

void handle_sp_approx(SP_APPROX sp_approx, int argc, char **argv) {
    cout << "#################" << endl;
    cout << "##  SP_APPROX  ##" << endl;
    cout << "#################" << endl;


    cout << "Using FASTA file: " << argv[2] << endl;
}

int main(int argc, char** argv) {
    Parser parser(argv[2]);

    if (strcmp(argv[1], "sp_exact_3") == 0) {
        SP_EXACT_3 sp_exact;
        sp_exact.initialize(parser);
        handle_sp_exact_3(sp_exact, argc, argv);
    } else if (strcmp(argv[1], "sp_approx") == 0) {
        cout << "#################" << endl;
        cout << "##  SP_APPROX  ##" << endl;
        cout << "#################" << endl;
        SP_APPROX sp_approx;
        sp_approx.initialize(parser);

    } else if (strcmp(argv[1], "both") == 0) {
        cout << parser.sequences[0].size() << "\t";
        SP_APPROX sp_approx;
        SP_EXACT_3 sp_exact_3;

        sp_approx.initialize(parser);
        sp_approx.compute_D();
        cout << sp_approx.getScore() << "\t";

        sp_exact_3.initialize(parser);
        sp_exact_3.compute_D();
        cout << sp_exact_3.getScore() << endl;


    } else {
        cerr << "Unknown algorithm. Argument 1 must be either 'sp_exact_3', 'sp_approx' or 'both'. ";
        cerr << "Got: '" << argv[1] << "'" << endl;
        return EXIT_FAILURE;
    }

/*
    
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
        */
    /*

    SP_APPROX sp_approx;
    sp_approx.initialize(parser);
    sp_approx.compute_D();
  */
    return EXIT_SUCCESS;
}

