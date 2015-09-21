/* -------------------------------------------------------------------------------------
** This software is implemented as part of the course
**     Algorithms in Bioinformatics - Sequences Q1/2015
** at Aarhus Univerity Denmark.
**
** Parser.h
** Responsible for parsing the score and fasta file
**
** Author: Martin Storgaard, Konstantinos Mampentzidis and Henrik McQuoid Jespersen
** -----------------------------------------------------------------------------------*/

#ifndef BIOSEQ_PROJECT3_PARSER_H
#define BIOSEQ_PROJECT3_PARSER_H


#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <algorithm>
using namespace std;

class Parser {
public:
    // The gap cost
    int64_t gap_cost;
    // The allowed alphabet sigma/proteins. Vector is size |Sigma|
    vector<char> proteins;
    // The score matrix of size |Sigma|x|Sigma|
    vector<vector<int64_t>> score;
    // A vector of size k x n containing the sequences. Note that it is a sequence of indices, not proteins,
    // i.e. an entry can be used to look-up a score directly
    vector<vector<char>> sequences;
    // A vector of size k, each containing the comment given in the input file, e.g. >seq1_10
    vector<string> sequence_comment;

    /**
     * Prepares all public variables, i.e. parsing the score and fasta file.
     */
    Parser(const char* filename) {
        // Parse the score file
        parse_score_file();
        // Parse the fasta file
        parse_fasta_file(filename);

    }

private:
    void parse_score_file();

    void parse_fasta_file(const char *&filename);
};


#endif //BIOSEQ_PROJECT3_PARSER_H
