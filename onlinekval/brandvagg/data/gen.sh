#!/bin/bash
REQUIRE_SAMPLE_REUSE=0
. ../../../testdata_tools/gen.sh

use_solution joshua.cpp

compile generate_many_limits.py
compile generate_many_logs.py
compile generate_random.py

samplegroup
sample sample01
sample sample02
sample sample03



group g1 7
# P <= 10,000. There are only "accept" actions.
tc g1-1 generate_random 100 10000 100 100 1
tc g1-2 generate_random 100 10000 10 10 1

group g2 15
# P <= 10,000. No rule has a condition.
tc g2-1 generate_random 100 10000 100 100 2
tc g2-2 generate_many_logs 100 2000 1 1 1
tc g2-3 generate_many_logs 100 2000 100 100 2

group g3 29
# P <= 10,000. There are no "limit" conditions.
tc g3-1 generate_random 100 10000 10 10 3
tc g3-2 generate_random 100 10000 10 10 3
tc g3-3 generate_random 100 10000 2 2 3
tc g3-4 generate_random 100 10000 40 40 3
tc g3-5 generate_random 100 10000 500 500 3


group g4 25
# P <= 100$
tc g4-1 generate_random 100 100 10 10 4
tc g4-2 generate_random 100 100 10 10 4
tc g4-3 generate_random 100 100 2 2 4
tc g4-4 generate_random 100 100 30 30 4
tc g4-5 generate_many_limits 100 100

group g5 14
include_group g4
# P <= 1,000
tc g5-1 generate_random 100 1000 10 10 4
tc g5-2 generate_random 100 1000 10 10 4
tc g5-3 generate_random 100 1000 2 2 4
tc g5-4 generate_random 100 1000 40 40 4
tc g5-5 generate_random 100 1000 500 500 4
tc g5-6 generate_many_limits 100 1000

group g6 10
include_group g1
include_group g2
include_group g3
include_group g5
# P <= 10,000
tc g6-1 generate_random 100 10000 10 10 4
tc g6-2 generate_random 100 10000 10 10 4
tc g6-3 generate_random 100 10000 2 2 4
tc g6-4 generate_random 100 10000 40 40 4
tc g6-5 generate_random 100 10000 500 500 4
tc g6-6 generate_many_limits 100 10000

