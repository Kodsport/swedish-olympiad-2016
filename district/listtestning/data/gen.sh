#!/bin/bash
REQUIRE_SAMPLE_REUSE=0
. ../../../testdata_tools/gen.sh

ulimit -s unlimited
use_solution listtestning_sl.py

compile gen.py

samplegroup
sample 1

group group01 6
tc g1-1 gen g=1

group group02 6
tc g1-2 gen g=2

group group03 6
tc g1-3 gen g=3

group group04 6
tc g1-4 gen g=4

group group05 6
tc g1-5 gen g=5

group group06 6
tc g1-6 gen g=6

group group07 6
tc g1-7 gen g=7

group group08 6
tc g1-8 gen g=8

group group09 6
tc g1-9 gen g=9

group group10 6
tc g1-10 gen g=10
