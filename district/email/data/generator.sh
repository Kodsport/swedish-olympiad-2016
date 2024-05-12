#!/bin/bash
REQUIRE_SAMPLE_REUSE=0
. ../../../testdata_tools/gen.sh

ulimit -s unlimited
use_solution email_sl.cpp

compile gen_rand.py
compile gen_semihard.py
compile gen_longpaths.py
compile gen_chains.py
compile gen_star.py

samplegroup
sample 1
sample 2

group group1 20
tc_manual ../manual_data/g1-1.in
tc_manual ../manual_data/g1-2.in

group group2 30
tc_manual ../manual_data/g2-1.in
tc_manual ../manual_data/g2-2.in

group group3 25
tc_manual ../manual_data/g3-1.in
tc_manual ../manual_data/g3-2.in

group group4 25
tc_manual ../manual_data/g4-1.in
tc_manual ../manual_data/g4-2.in
