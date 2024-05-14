#!/bin/bash
. ../../../testdata_tools/gen.sh

use_solution namnsdag_js.py

compile gen_rand.cc

samplegroup
sample sample1
sample sample2
sample sample3

group g1 53
include_group sample
tc g1-1 gen_rand 50 2
tc g1-2 gen_rand 49 3
tc g1-3 gen_rand 48 3
tc g1-4 gen_rand 47 3
tc g1-5 gen_rand 46 4
tc g1-6 gen_rand 45 5
tc g1-7 gen_rand 44 10
tc g1-8 gen_rand 1 3
tc_manual 1
tc_manual 2
tc_manual 3
tc_manual 4


group group2 47
include_group g1
tc g2-1 gen_rand 1 1
tc g2-2 gen_rand 5 10
tc g2-3 gen_rand 500 10
tc g2-4 gen_rand 5000 10
tc g2-5 gen_rand 10000 10
tc g2-6 gen_rand 10000 7
tc g2-7 gen_rand 10000 5
tc g2-8 gen_rand 10000 3
