cmake_minimum_required(VERSION 3.2)
project(BioSeq_Project3)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "lib/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "lib/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

set(CMAKE_CXX_FLAGS "-O3  -Wall -std=c++0x -march=native")

set(SOURCE_FILES
        src/main.cpp)

set(ALIGNMENT_ALGS
        src/MSA.h src/Parser.cpp src/Parser.h src/SP_EXACT_3.h src/SP_EXACT_3.cpp src/SP_APPROX.h src/SP_APPROX.cpp)

add_executable(BioSeq_Project3 ${ALIGNMENT_ALGS} ${SOURCE_FILES})