#!/bin/bash
PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

use_solution godis_sl.cpp

compile generate_random.py
compile generate_single.py

samplegroup
sample sample01

group g1 25
# N <= 15
tc sample01
tc g1-1 generate_single 15 10
tc g1-2 generate_random 15 10
tc g1-3 generate_random 15 10
tc g1-4 generate_random 15 10
tc g1-5 generate_random 15 10
tc g1-6 generate_random 15 4
tc g1-7 generate_random 15 4
tc g1-8 generate_random 15 3

group g2 25
# N <= 1000. Every bag has just one type of candy.
tc g2-1 generate_single 1000 10
tc g2-2 generate_single 1000 10
tc g2-3 generate_single 1000 10

group g3 50
include_group g1
include_group g2
# N <= 1000
tc g3-1 generate_random 15 10
tc g3-2 generate_random 15 3
tc g3-3 generate_random 1000 10
tc g3-4 generate_random 1000 10
tc g3-5 generate_random 1000 10
tc g3-6 generate_random 1000 10
tc g3-7 generate_single 1000 10
tc g3-8 generate_single 1000 10
