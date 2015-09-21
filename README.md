# Algorithms in Bioinformatics - Sequences Q1/2015
### By Martin Storgaard, Konstantinos Mampentzidis and Henrik McQuoid Jespersen

This project is about implementing the exact (dynamic programming based) and the 2-approximation algorithm for global
sum-of-pairs multiple alignment.

# How to compile
This project depends on `cmake` version 3.2 and is only tested on Ubuntu 14.04. To get the latest `cmake` run
the following:

```bash
sudo add-apt-repository ppa:george-edison55/cmake-3.x
sudo apt-get update
```

If `cmake` is already installed, use: `sudo apt-get upgrade`, otherwise use `sudo apt-get install cmake`

To compile all sources, run `./make.sh` (or the usual `cmake` command, the bash scripts ensures uniformity).

# The scripts

`./experiment1.sh`, `./experiment2.sh` and `./experiment3.sh` runs the corresponding experiment given in the project
description.

TODO: `./sp_exact_3.sh`

TODO: `./sp_approx.sh`