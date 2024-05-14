#!/bin/bash
PPATH=$(realpath ..)
. ../../../../testdata_tools/gen.sh


use_solution ../regskylt_js.cpp

compile random_generator.py # Arguments: n k case seed

samplegroup
sample 1

group 1-known 13
tc known-1 random_generator 100000 1 known
tc known-2 random_generator 100000 2 known
tc known-3 random_generator 100000 10 known
tc known-4 random_generator 100000 100 known
tc known-5 random_generator 100000 1000 known
tc known-6 random_generator 100000 10000 known
tc known-7 random_generator 100000 100000 known

group 2-zeroes 31
tc zeroes-1 random_generator 100000 1 zeroes
tc zeroes-2 random_generator 100000 1 zeroes

group 3-small 20
tc 1
tc small-1 random_generator 1000 1 ''
tc small-2 random_generator 1000 2 ''
tc small-3 random_generator 1000 10 ''
tc small-4 random_generator 1000 100 ''
tc small-5 random_generator 1000 1000 ''

group 4-large 36
include_group 1-known
include_group 2-zeroes
include_group 3-small
tc large-1 random_generator 100000 1 ''
tc large-2 random_generator 100000 2 ''
tc large-3 random_generator 100000 10 ''
tc large-4 random_generator 100000 100 ''
tc large-5 random_generator 100000 1000 ''
tc large-6 random_generator 100000 10000 ''
tc large-7 random_generator 100000 100000 ''

