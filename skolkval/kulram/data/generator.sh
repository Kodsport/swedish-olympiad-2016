#!/bin/bash
. ../../../testdata_tools/gen.sh


ulimit -s unlimited
use_solution kulram.cc


samplegroup
sample sample01
sample sample02
sample sample03
sample sample04


group group1 20
tc sample01
tc sample02
tc sample03
tc_manual 1

group group2 40
include_group group1
tc_manual 2
tc_manual 3

group group3 40
include_group group2
tc sample04
tc_manual 4
tc_manual 5
