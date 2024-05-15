#!/bin/bash
PPATH=$(realpath ..)
. ../../../../testdata_tools/gen.sh

ulimit -s unlimited
use_solution ../joshua.cpp

compile random_letter.py # Arguments: N P_a seed
compile random_aa.py # Arguments: N P_a aa seed

samplegroup
sample 1

group 1-small 9
tc 1
tc small01 random_letter 100 10
tc small02 random_letter 100 20
tc small03 random_letter 100 50
tc small04 random_aa 100 80 0
tc small05 random_aa 100 50 20
tc small06 random_letter 100 10

group 2-mid 11
include_group 1-small
tc mid01 random_letter 5000 10
tc mid02 random_letter 5000 20
tc mid03 random_letter 5000 50
tc mid04 random_aa 5000 80 0
tc mid05 random_aa 5000 50 200
tc mid06 random_aa 5000 20 1000

group 3-uniform 14
tc uniform01 random_letter 100000 50
tc uniform02 random_letter 100000 50

group 4-fibonacci 25
tc fibonacci01 random_aa 100000 10 0
tc fibonacci02 random_aa 100000 40 0
tc fibonacci03 random_aa 100000 70 0

group 5-all 41
include_group 2-mid
include_group 3-uniform
include_group 4-fibonacci
tc large01 random_letter 100000 10
tc large02 random_letter 100000 20
tc large03 random_letter 100000 50
tc large04 random_aa 100000 80 0
tc large05 random_aa 100000 50 2000
tc large06 random_aa 100000 20 10000
