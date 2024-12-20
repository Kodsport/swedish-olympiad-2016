#!/bin/bash
PPATH=$(realpath ..)
. ../../../../../testdata_tools/gen.sh

use_solution sol.cpp

compile randomGenerator.cpp # Arguments: n k seed
compile longChainGenerator.cpp # Arguments: n k seed
compile completeGenerator.cpp # Arguments: n k seed
compile genWorstCase.cpp # Arguments: n seed
compile genStar.cpp # Arguments: n seed

samplegroup
limits N=100000
sample 1

# N <= 100
group g1 9
limits N=100
tc 1
tc small-1 randomGenerator 100 1
tc small-2 randomGenerator 100 5
tc small-3 randomGenerator 100 10
tc small-4 randomGenerator 100 10
tc small-5 randomGenerator 100 50
tc small-6 randomGenerator 100 100
tc small-7 longChainGenerator 100 25
tc small-8 longChainGenerator 100 50
tc small-9 genWorstCase 100
tc small-10 genStar 100

# N <= 1000
group g2 19
limits N=1000
include_group g1
tc medium-1 randomGenerator 1000 1
tc medium-2 randomGenerator 1000 5
tc medium-3 randomGenerator 1000 20
tc medium-4 randomGenerator 1000 30
tc medium-5 randomGenerator 1000 100
tc medium-6 randomGenerator 1000 1000
tc medium-7 longChainGenerator 1000 250
tc medium-8 longChainGenerator 1000 500
tc medium-9 genWorstCase 1000
tc medium-10 genStar 1000

# N <= 100,000, K <= 10
group g3 34
limits N=100000 K=10
tc 1
tc smallk-1 randomGenerator 100000 1
tc smallk-2 randomGenerator 100000 4
tc smallk-3 randomGenerator 100000 10
tc smallk-4 randomGenerator 100000 10
tc smallk-5 randomGenerator 100000 10
tc smallk-6 longChainGenerator 100000 10

# N <= 100,000
group g4 38
limits N=100000
include_group g2
include_group g3
tc large-1 randomGenerator 100000 50
tc large-2 randomGenerator 100000 100
tc large-3 randomGenerator 100000 300
tc large-4 randomGenerator 100000 400
tc large-5 randomGenerator 100000 500
tc large-6 randomGenerator 100000 2000
tc large-7 randomGenerator 100000 20000
tc large-8 randomGenerator 100000 100000
tc longest-1 longChainGenerator 100000 25000
tc longest-2 longChainGenerator 100000 50000
tc large-9 genWorstCase 100000
tc large-10 genStar 100000
