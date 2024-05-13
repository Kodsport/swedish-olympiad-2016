#!/bin/bash
. ../../../testdata_tools/gen.sh


ulimit -s unlimited
use_solution parsod_dp.cc

compile gen_rand.py

samplegroup
limits maxn=10
sample sample01
sample sample02
sample sample03

group group1 20
limits maxn=1
tc g1-1 gen_rand n=1
tc g1-2 gen_rand n=1
tc g1-3 gen_rand n=1
tc g1-4 gen_rand n=1

group group2 20
limits maxn=2
include_group group1
tc sample03
tc g2-1 gen_rand n=2
tc g2-2 gen_rand n=2
tc g2-3 gen_rand n=2
tc g2-4 gen_rand n=2

group group3 30
limits maxn=5
include_group group2
tc sample01
tc g3-1 gen_rand n=5
tc g3-2 gen_rand n=5
tc g3-3 gen_rand n=5
tc g3-4 gen_rand n=5

group group4 30
limits maxn=15
include_group group3
tc sample02
tc g4-1 gen_rand n=15
tc g4-2 gen_rand n=15
tc g4-3 gen_rand n=15
tc g4-4 gen_rand n=15
