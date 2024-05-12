#!/bin/bash
. ../../../testdata_tools/gen.sh

# Choose your solution
use_solution joshua.cpp

# Compile generators
compile gen-random.py # Arguments: length seed

# Generate answers to sample cases
samplegroup
limits maxn=20
sample 1
sample 2
sample 3

group group1 7
limits maxn=11
tc 1
tc 3
tc exact gen-random n=10
tc one_off_01 gen-random n=11
tc one_off_02 gen-random n=11
tc one_off_03 gen-random n=11

group group2 11
limits maxn=100
include_group group1
tc 2
tc rand100 gen-random n=100
tc sparse100 gen-random n=100 alphabet=UNVA

group group3 12
limits maxn=3000
include_group group2
tc rand3000 gen-random n=3000
tc sparse3000 gen-random n=3000 alphabet=UNVA
tc sparse3000-2 gen-random n=2999 alphabet=UA

group group4 20
limits maxn=200000
include_group group3
tc rand200000 gen-random n=200000
tc sparse200000 gen-random n=200000 alphabet=UNVA
tc sparse200000-2 gen-random n=199997 alphabet=UA
