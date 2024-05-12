#!/bin/bash
PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

use_solution labb_sl.cpp

compile random_generator.py # Arguments: case npresentations seed

samplegroup
sample sample

group g1 30 # there are at most 10 presentations
tc sample
tc g1-1 random_generator '' 10
tc g1-2 random_generator '' 10

group g2 17 # all presentations are equally long
tc g2 random_generator equal 5000

group g3 13 # everyone has exactly two presentations
tc g3 random_generator two 5000

group g4 18
include_group g3
include_group g2
include_group g1
tc medium random_generator '' 5000

group g5 22 # sum of m_i <= 100,000
include_group g4
tc large random_generator '' 100000
