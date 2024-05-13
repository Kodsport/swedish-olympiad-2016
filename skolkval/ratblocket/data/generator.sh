#!/bin/bash
. ../../../testdata_tools/gen.sh


ulimit -s unlimited
use_solution parsod_bfs.cc


samplegroup
sample sample1
sample sample2
sample sample3

group group1 40
tc sample1
tc sample2
tc_manual 1
tc_manual 2

group group2 60
include_group group1
tc sample3
tc_manual 3
tc_manual 4
tc_manual 5
