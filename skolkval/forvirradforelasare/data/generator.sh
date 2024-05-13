#!/bin/bash
. ../../../testdata_tools/gen.sh


ulimit -s unlimited
use_solution parsod.py


samplegroup
sample sample01
sample sample02
sample sample03


group group1 100
tc sample01
tc sample02
tc sample03
tc_manual 1
tc_manual 2
tc_manual 3
tc_manual 4
tc_manual 5
