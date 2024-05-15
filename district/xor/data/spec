#!/bin/bash
PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

# Choose your solution
use_solution joshua.cpp

# Compile generators
compile fish-gen.py # Arguments: length seed

# Generate answers to sample cases
samplegroup
sample sample

# Add a new testdata group

add_case() {
  for x in ../texts/*
  do
    txt=`basename $x`
    transform=$1
    keylen=$2
    echo $txt $keylen $transform
    tc "$txt-$transform-$keylen" fish-gen $txt $keylen $transform
  done
}

group 1-single-az 6
add_case az 1

group 2-single 10
add_case none 1

group 3-five-fisk 12
tc sample
add_case fisk 3
add_case fisk 4
add_case fisk 5

group 4-five-az 19
add_case az 3
add_case az 4
add_case az 5

group 5-five 24
include_group 2-single
include_group 3-five-fisk
include_group 4-five-az
add_case none 3
add_case none 4
add_case none 5

group 6-ten-az 33
include_group 4-five-az
add_case az 8
add_case az 9
add_case az 10

group 7-ten 41
include_group 5-five
include_group 6-ten-az
add_case none 8
add_case none 9
add_case none 10

group 8-flagpole 15
add_case flagpole 15

