#!/bin/bash
PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited
use_solution gratismat_js.cpp

compile completeGenerator.cpp
compile longChainGenerator.cpp
compile randomGenerator.cpp

samplegroup
sample sample0
sample sample1

group g1 49
# N <= 2000
tc sample0
tc sample1
tc g1-1 randomGenerator 16 8
tc g1-2 completeGenerator 15 4
tc g1-3 longChainGenerator 2000
tc g1-4 completeGenerator 2000 100
tc g1-5 completeGenerator 2000 1000
tc g1-6 randomGenerator 2000 10
tc g1-7 randomGenerator 2000 100
tc g1-8 randomGenerator 2000 1000
tc g1-9 randomGenerator 2000 2000

group g2 51
include_group g1
# N <= 100000
tc g2-1 longChainGenerator 100000
tc g2-2 completeGenerator 100000 1000
tc g2-3 completeGenerator 100000 10000
tc g2-4 randomGenerator 100000 100
tc g2-5 randomGenerator 100000 1000
tc g2-6 randomGenerator 100000 10000
tc g2-7 randomGenerator 100000 50000
