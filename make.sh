#!/usr/bin/env bash
# Force use of g++ version 4.8
CXX=g++-4.8 cmake .
# Make the project using the generated Makefile
make