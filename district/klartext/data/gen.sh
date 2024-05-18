#!/bin/bash
REQUIRE_SAMPLE_REUSE=0
PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

# Choose your solution
use_solution solution.py

# Compile generators
compile gen-random.py # Arguments: type

# Generate answers to sample cases
samplegroup
for x in sample/*.in
do
  sample `basename ${x%.*}`
done

# Add a new testdata group
group 1-caesar 10
for i in {1..10}
do
tc caesar-$i gen-random caesar
done

group 2-fixed 15
for i in {1..10}
do
tc fixed-$i gen-random railgun
done

group 3-railgun 25
for i in {1..10}
do
tc railgun-$i gen-random fixed_hard
done

group 4-dynamic 25
for i in {1..10}
do
tc dynamic-$i gen-random dynamic_permutation
done

group 5-morse 40
for i in {1..10}
do
tc morse-$i gen-random morse
done
