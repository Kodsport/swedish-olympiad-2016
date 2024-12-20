#!/bin/bash
PPATH=$(realpath ..)
. ../../../../testdata_tools/gen.sh


use_solution ../sol.cpp

compile gen.py # Arguments: n m type seed

samplegroup
sample 1

# N, K <= 100,000 M <= 10^9
group 1-nocycle 15
tc nocycle1 gen 999 990000002 nocycle
tc nocycle2 gen 50001 990000004 nocycle
tc nocycle3 gen 99998 990000003 nocycle
tc nocycle4 gen 999 500 nocycle
tc nocycle5 gen 50001 250 nocycle
tc nocycle6 gen 99998 500 nocycle
tc path3 gen 99991 40000 path
tc path4 gen 99991 40000 path

# N, K <= 100,000 M <= 10^9
group 2-cycle 15
tc cycle1 gen 998 900000203 cycle
tc cycle2 gen 50002 902200004 cycle
tc cycle3 gen 99999 900220001 cycle

# N, K, M <= 1000
group 3-small 15
tc 1
tc small1 gen 1000 1000 random
tc small2 gen 1000 1000 random
tc path1 gen 999 1000 path
tc reverse1 gen 950 1000 reverse
tc cycle gen 996 1000 cycle2

# N, K <= 1000, M <= 10^9
group 4-mid 15
include_group 3-small
tc mid1 gen 998 901000003 random
tc mid2 gen 980 900000301 random
tc path2 gen 999 900020002 path
tc reverse2 gen 997 900010004 reverse
tc cycle1
tc cycle4 gen 998 900000203 cycle2

# N, K <= 100,000 M <= 10^9
group 5-large 40
include_group 4-mid
include_group 1-nocycle
include_group 2-cycle
tc large1 gen 99993 903000002 random
tc large gen 99994 900003004 random
tc reverse3 gen 99992 900001007 reverse
tc cycle5 gen 50002 902200004 cycle2
tc cycle6 gen 99999 900220001 cycle2
