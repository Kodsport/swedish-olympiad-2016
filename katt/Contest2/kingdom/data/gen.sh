#!/bin/bash
PPATH=$(realpath ..)
. ../testdata_tools/gen.sh



use_solution ../sol.cpp

compile randomGenerator.cpp # Arguments: n k each case seed
compile genPath.py # Arguments: n each seed
compile genOverflow.py
compile genOverflow2.py

samplegroup
sample 1

# P = 2, N <= 1000
group 1-two 8
tc overflow-1 genOverflow
tc overflow-2 genOverflow2
tc two-random-yes-1 randomGenerator 1000 2 3 yes,two
tc two-random-yes-2 randomGenerator 1000 2 10 yes,two
tc two-random-yes-3 randomGenerator 1000 2 100 yes,two
tc two-random-no-1 randomGenerator 1000 1 4000 no,two
tc two-random-no-2 randomGenerator 1000 1 10000 no,two
tc two-random-no-3 randomGenerator 1000 1 10000 no,two

# N <= 1000, C_i > 0
group 2-medium_pos 10
tc overflow-1
tc overflow-2
tc medium-pos-random-yes-1 randomGenerator 1000 5 10000 yes,pos
tc medium-pos-random-yes-2 randomGenerator 1000 10 10000 yes,pos
tc medium-pos-random-yes-3 randomGenerator 1000 200 10000 yes,pos
tc medium-pos-random-no-1 randomGenerator 1000 5 10000 no,pos
tc medium-pos-random-no-2 randomGenerator 1000 10 10000 no,pos
tc medium-pos-random-no-3 randomGenerator 1000 200 10000 no,pos

# N <= 1000, the tree is a line
group 3-line 16
tc overflow-1
tc overflow-2
tc path-1 genPath 1000 1
tc path-2 genPath 1000 2
tc path-3 genPath 1000 -5
tc path-4 genPath 1000 100

# N <= 1000
group 4-medium 18
include_group 1-two
include_group 2-medium_pos
include_group 3-line
tc 1
tc medium-random-yes-1 randomGenerator 1000 5 1000 yes
tc medium-random-yes-2 randomGenerator 1000 10 100 yes
tc medium-random-yes-3 randomGenerator 1000 200 10 yes
tc medium-random-no-1 randomGenerator 1000 20 1000 no
tc medium-random-no-2 randomGenerator 1000 50 100 no
tc medium-random-no-3 randomGenerator 1000 500 10 no

# N <= 100,000, C_i > 0
group 5-large_pos 18
include_group 2-medium_pos
tc large-pos-random-yes-1 randomGenerator 100000 20 200000 yes,pos
tc large-pos-random-yes-2 randomGenerator 100000 500 2000000 yes,pos
tc large-pos-random-yes-3 randomGenerator 100000 30000 200000 yes,pos
tc large-pos-random-no-1 randomGenerator 100000 200 200000 no,pos
tc large-pos-random-no-2 randomGenerator 100000 5000 2000000 no,pos
tc large-pos-random-no-3 randomGenerator 100000 30000 100000 no,pos


# N <= 100,000
group 6-large 30
include_group 5-large_pos
include_group 4-medium
tc large-random-yes-1 randomGenerator 100000 20 1000 yes
tc large-random-yes-2 randomGenerator 100000 500 100 yes
tc large-random-yes-3 randomGenerator 100000 30000 10 yes
tc large-random-no-1 randomGenerator 100000 200 1000 no
tc large-random-no-2 randomGenerator 100000 5000 100 no
tc large-random-no-3 randomGenerator 100000 30000 10 no
