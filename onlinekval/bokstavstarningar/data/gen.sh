#!/bin/bash
. ../../../testdata_tools/gen.sh

use_solution simon.cpp

compile generator_random.py

samplegroup
sample sample01

group g1 9
tc g1-1 generator_random 2 4 2
tc g1-2 generator_random 2 3 2

group g2 9
include_group g1
tc sample01
tc g2-1 generator_random 2 5 6
tc g2-2 generator_random 3 4 5
tc g2-3 generator_random 3 5 2

group g3 12
include_group g2
tc g3-1 generator_random 2 6 20
tc g3-2 generator_random 3 6 10
tc g3-3 generator_random 3 6 3

group g4 14
tc g4-1 generator_random 2 6 15
tc g4-2 generator_random 3 6 10
tc g4-3 generator_random 3 6 3

group g5 21
include_group g3
include_group g4
tc g5-1 generator_random 2 6 20
tc g5-2 generator_random 3 6 10
tc g5-3 generator_random 3 6 3

group g6 35
tc g6-1 generator_random 2 13 10
tc g6-2 generator_random 2 6 10
tc g6-3 generator_random 2 6 3
tc g6-4 generator_random 2 13 3
