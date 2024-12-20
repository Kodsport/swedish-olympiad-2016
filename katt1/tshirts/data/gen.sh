#!/bin/bash
PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh


use_solution ../tshirts.cpp

compile random_generator.py # Arguments: N T method seed

samplegroup
sample 1

group 1-dp1 7
tc 1
tc dp1-01 random_generator 10 1000 random
tc dp1-02 random_generator 10 1000 random
tc dp1-03 random_generator 10 1000 random
tc dp1-04 random_generator 10 1000 random
tc dp1-05 random_generator 10 1000 none
tc dp1-06 random_generator 10 1000 none
tc dp1-07 random_generator 10 1000 all_unique
tc dp1-08 random_generator 10 1000 all_unique
tc dp1-09 random_generator 10 1000 dense
tc dp1-10 random_generator 10 1000 dense
tc dp1-11 random_generator 10 1000 sim_random
tc dp1-12 random_generator 10 1000 sim_random
tc dp1-13 random_generator 10 1000 sim_random2
tc dp1-14 random_generator 10 1000 sim_random2

group 2-dp2 24
include_group 1-dp1
tc dp2-01 random_generator 1000 1000 random
tc dp2-02 random_generator 1000 1000 random
tc dp2-03 random_generator 1000 1000 random
tc dp2-04 random_generator 1000 1000 random
tc dp2-05 random_generator 500 1000 none
tc dp2-06 random_generator 500 1000 none
tc dp2-07 random_generator 1000 1000 all_unique
tc dp2-08 random_generator 1000 1000 all_unique
tc dp2-09 random_generator 1000 1000 dense
tc dp2-10 random_generator 1000 1000 dense
tc dp2-11 random_generator 1000 1000 dense
tc dp2-12 random_generator 1000 1000 dense
tc dp2-13 random_generator 1000 1000 sim_random
tc dp2-14 random_generator 1000 1000 sim_random
tc dp2-15 random_generator 1000 1000 sim_random2
tc dp2-16 random_generator 1000 1000 sim_random2

group 3-special 13
tc special-01 random_generator 100000 1 random
tc special-02 random_generator 100000 1 random
tc special-03 random_generator 100000 1 random
tc special-04 random_generator 100000 1 random
tc special-05 random_generator 1 1 none
tc special-06 random_generator 2 1 all_unique
tc special-07 random_generator 100000 1 biased0
tc special-08 random_generator 100000 1 biased1

group 4-greedyslow 37
include_group 1-dp1
include_group 2-dp2
include_group 3-special
tc greedyslow-01 random_generator 100000 100000 random
tc greedyslow-02 random_generator 100000 100000 random
tc greedyslow-03 random_generator 50000 100000 none
tc greedyslow-04 random_generator 50000 100000 none
tc greedyslow-05 random_generator 100000 100000 all_unique
tc greedyslow-06 random_generator 100000 100000 all_unique
tc greedyslow-07 random_generator 100000 100000 dense
tc greedyslow-08 random_generator 100000 100000 dense
tc greedyslow-09 random_generator 100000 100000 sim_random
tc greedyslow-10 random_generator 100000 100000 sim_random
tc greedyslow-11 random_generator 100000 100000 sim_random2
tc greedyslow-12 random_generator 100000 100000 sim_random2

group 5-greedy 19
include_group 1-dp1
include_group 2-dp2
include_group 3-special
include_group 4-greedyslow
tc greedy-01 random_generator 100000 1000000000 random
tc greedy-02 random_generator 100000 1000000000 random
tc greedy-03 random_generator 100000 1000000000 none
tc greedy-04 random_generator 100000 1000000000 none
tc greedy-05 random_generator 100000 1000000000 all_unique
tc greedy-06 random_generator 100000 1000000000 all_unique
tc greedy-07 random_generator 100000 1000000000 dense
tc greedy-08 random_generator 100000 1000000000 dense
tc greedy-09 random_generator 100000 1000000000 sim_random
tc greedy-10 random_generator 100000 1000000000 sim_random
tc greedy-11 random_generator 100000 1000000000 sim_random2
tc greedy-12 random_generator 100000 1000000000 sim_random2
