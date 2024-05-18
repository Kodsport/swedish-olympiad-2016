#!/bin/bash
PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh


# Choose your solution
use_solution mars_js.cpp

# Compile generators
compile random_generator.py # Arguments: integer seed

# Generate answers to sample cases
samplegroup
sample sample

# Add a new testdata group
group ints 46
# Note: tc automatically adds a deterministic, pseudo-random seed argument to your generator
tc sample
tc ints random_generator integers 50000

group floats 54
include_group ints
tc floats random_generator floats 50000