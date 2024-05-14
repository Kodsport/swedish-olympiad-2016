#!/bin/bash
PPATH=$(realpath ..)
. ../testdata_tools/gen.sh


use_solution ../sol.cpp

compile random_generator.py # Arguments: n k case seed

samplegroup
sample 1

# N <= 100
group 1-small 20
tc 1
tc small-1 random_generator 100 100 ''
tc small-2 random_generator 100 100 ''
tc small-3 random_generator 100 100 ''
tc small-4 random_generator 100 100 ''
tc small-5 random_generator 100 100 ''
tc small-6 random_generator 100 100 ''
tc small-7 random_generator 100 100 ''
tc small-nn-1 random_generator 100 100 nonneg
tc small-two-1 random_generator 100 100 two

# N <= 1000, L[i] >= 0
group 2-nonneg 20
tc nonneg-1 random_generator 1000 1000 nonneg
tc nonneg-2 random_generator 1000 1000 nonneg
tc nonneg-3 random_generator 1000 1000 nonneg
tc nonneg-4 random_generator 1000 1000 nonneg
tc nonneg-5 random_generator 1000 1000 nonneg

# N <= 1000, R[i] - L[i] = 2
group 3-two 20
tc two-1 random_generator 1000 1000 two
tc two-2 random_generator 1000 1000 two
tc two-3 random_generator 1000 1000 two
tc two-4 random_generator 1000 1000 two

# N <= 1000
group 4-large 40
include_group 1-small
include_group 2-nonneg
include_group 3-two
tc large-1 random_generator 1000 1000 ''
tc large-2 random_generator 1000 1000 ''
tc large-3 random_generator 1000 1000 ''
tc large-4 random_generator 1000 1000 ''
tc large-5 random_generator 1000 1000 ''
tc large-6 random_generator 1000 1000 ''
tc large-7 random_generator 1000 1000 ''
