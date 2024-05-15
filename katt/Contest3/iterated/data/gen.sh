#!/bin/bash
. ../../../../testdata_tools/gen.sh


ulimit -s unlimited
use_solution ../dummy.cpp

compile gen_rand.py
compile gen_full.py
compile gen_cycle_nowalk.py
compile gen_cycle_walk.py

samplegroup
sample 1
sample 2
sample 3
sample 4


group2 g1 1 exp
repeat 2 testcase 10

group2 g2 1 2n
repeat 2 testcase 5000

group2 g3 1 n 5000
repeat 2 testcase 5000

group1 g4 1 rel 5000
