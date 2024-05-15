#!/bin/bash
. ../../../testdata_tools/gen.sh


use_solution fragetavling_sl.cpp
compile random_generator.py # Arguments: n m k b seed
compile samescore_generator.py # Arguments: n m k score b seed

samplegroup
sample sample01
sample sample02

group 1-onecat 16 # N <= 100, M = 1
tc onecat-notall-1 random_generator 100 1 20 10000
tc onecat-notall-2 random_generator 100 1 90 1
tc onecat-all-1    random_generator 100 1 100 100000

group 2-fivecat 29 # M <= 5
include_group 1-onecat
tc sample01
tc sample02
tc fivecat-notall-1 random_generator 1000 5 4 0.3
tc fivecat-notall-2 random_generator 1000 5 20 0.3
tc fivecat-notall-3 random_generator 1000 5 900 0.1
tc fivecat-notall-4 random_generator 1000 5 900 0.8
tc fivecat-notall-5 random_generator 1000 5 900 1.3
tc fivecat-notall-6 random_generator 1000 5 900 1.3
tc fivecat-all-1    random_generator 1000 5 1000 0.9

group 3-samescore 20 # all questions have the same score
tc samescore-1 samescore_generator 1000 5 400 1 1
tc samescore-2 samescore_generator 1000 5 900 1 1000
tc samescore-3 samescore_generator 1000 50 500 1000 100000
tc samescore-4 samescore_generator 1000 900 900 1000 1000
tc samescore-5 samescore_generator 1000 900 40 1000 1

group 4-full 35
include_group 2-fivecat
include_group 3-samescore
tc full-1 random_generator 1000 50 40 0.1
tc full-2 random_generator 1000 50 400 0.7
tc full-3 random_generator 1000 50 400 1.3
tc full-4 random_generator 1000 60 900 1.0
tc full-5 random_generator 1000 100 900 1.0
tc full-6 random_generator 1000 500 50 0.2
tc full-7 random_generator 1000 500 500 1.0
tc full-8 random_generator 1000 900 900 0.1
