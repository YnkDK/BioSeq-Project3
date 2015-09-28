/* -------------------------------------------------------------------------------------
** This software is implemented as part of the course
**     Algorithms in Bioinformatics - Sequences Q1/2015
** at Aarhus Univerity Denmark.
**
** Parser.cpp
** Concrete implementations for parsing the score and fasta file.
**
** Author: Martin Storgaard, Konstantinos Mampentzidis and Henrik McQuoid Jespersen
** -----------------------------------------------------------------------------------*/

#include "Parser.h"

/**
 * Example of the config file:
 *  5
 *  A C g T
 *  0 5 2 5
 *  5 0 5 2
 *  2 5 0 5
 *  5 2 5 0
 *
 *  i.e.
 *  Line 1: Contains the gap cost
 *  Line 2: Contains the alphabet (not case sentitive)
 *  Line 3-|alphabet|: The score for any given combination, i.e. The (i,i)'th is the score of a match, all others
 *  are scores for miss. In the above example (0, 3) is a miss between A and G.
 */
void Parser::parse_score_file() {
    ifstream fin;
    string line;
    fin.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        fin.open("config/score.cfg");

        // Set the gap cost
        getline(fin, line);
        gap_cost = stoll(line);
        // Define the alphabet
        getline(fin, line);
        istringstream acids(line);
        string tmp;
        while (getline(acids, tmp, ' ')) {
            if (tmp.size() == 1) {
                char c = (char) toupper(tmp.c_str()[0]);

                proteins.push_back(c);
            }
        }
        // Set the score matrix
        const uint64_t SIZE = proteins.size();
        score.resize(SIZE, vector<int64_t>(SIZE));

        for (uint64_t i = 0; i < SIZE; i++) {
            getline(fin, line);
            istringstream current(line);
            uint64_t j = 0;
            while (getline(current, tmp, ' ')) {
                if (tmp.size() != 0) {
                    score[i][j] = stoll(tmp);
                    j++;
                }
            }
        }
        // Close the config file
        fin.close();
    } catch (ifstream::failure e) {
        cerr <<
        "Failed parsing config: Check that file exists, that permission are correct and that it is formatted correctly!" <<
        endl;
        exit(EXIT_FAILURE);
    } catch (invalid_argument e) {
        cerr << "Could not parse config: Failed to " << e.what() << endl;
    }
}

/**
 * Example of file structure:
 *  >seq1_10
 *  gaAGCG GTGC
 *  >seq2_10
 *  GAGGG
 *  GCGCC
 *  >seq3_10
 *  TT A
 *  ACAAC
 *  G G
 *
 * i.e. spaces and new lines are skipped. Likewise is the case ignored
 */
void Parser::parse_fasta_file(const char *&filename) {
    int k = -1;
    string tmp;
    ifstream fin;
    fin.exceptions(std::ifstream::failbit | std::ifstream::badbit);


    try {
        fin.open(filename);
        fin.exceptions(std::ifstream::badbit);
        while (getline(fin, tmp)) {
            if (tmp[0] == '>') {
                sequence_comment.push_back(tmp);
                sequences.push_back(vector<char>());
                k++;
            } else {
                for (char c : tmp) {
                    if (c == ' ') continue;
                    char idx = find(proteins.begin(), proteins.end(), toupper(c)) - proteins.begin();
                    if (idx == (char) proteins.size()) {
                        sequences[k].push_back(0);
//                        cerr << "Unknown protein '" << c << "'. Halting." << endl;
//                        cerr << "TODO: Implement this!" << endl;
//                        exit(EXIT_FAILURE);
                    } else {
                        sequences[k].push_back(idx);
                    }
                }
            }
        }
        fin.close();
    } catch (ifstream::failure e) {
        cerr << e.what() << endl;
        cerr <<
        "Failed parsing config: Check that file exists, that permission are correct and that it is formatted correctly!" <<
        endl;
        exit(EXIT_FAILURE);
    }

}
