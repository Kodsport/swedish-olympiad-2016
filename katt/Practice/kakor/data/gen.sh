#!/bin/bash
PPATH=$(realpath ..)
. ../../../../testdata_tools/gen.sh


use_solution ../kakor_js.cpp

compile random_generator.py # Arguments: n max_a seed

samplegroup
sample 1

group 1-one 27
tc one-mid random_generator 500 1
tc one-max random_generator 1000 1

group 2-normal 34
include_group 1-one
tc 1
tc rand-mid random_generator 500 100000
tc rand-max random_generator 1000 100000

group 3-overflow 39
include_group 2-normal
tc overflow-mid random_generator 50000 100000
tc overflow-max random_generator 100000 100000
