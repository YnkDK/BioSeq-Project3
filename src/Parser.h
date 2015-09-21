//
// Created by mys on 9/21/15.
//

#ifndef BIOSEQ_PROJECT3_PARSER_H
#define BIOSEQ_PROJECT3_PARSER_H


#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Parser {
public:
    int64_t gap_cost;
    vector<vector<int64_t>> score;


    Parser(const char* filename) {
        ifstream fin;
        fin.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
        try {
            fin.open("config/score.cfg");

            fin.close();
        } catch(ifstream::failure e) {
            cerr << "Failed parsing config: Check that file exists and permission is correct" << endl;
            exit(EXIT_FAILURE);
        }

    }

private:
    void parse_score_file();
};


#endif //BIOSEQ_PROJECT3_PARSER_H
