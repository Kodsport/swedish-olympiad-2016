#!/bin/bash
. ../../../testdata_tools/gen.sh

use_solution parsod.cc

compile gen_rand.py

samplegroup
sample sample01
sample sample02
sample sample03
sample sample04

group group1 20
limits maxn=10
tc sample01
tc_manual s1
for i in {1..5}
do
tc g1-$i gen_rand n=10
done

group group2 20
limits maxn=100
include_group group1
tc sample02
tc_manual s2
for i in {1..10}
do
tc g2-$i gen_rand n=100
done

group group3 40
limits maxn=10000
include_group group2
tc sample03
tc sample04
tc_manual s3
tc_manual s4
for i in {1..10}
do
tc g3-$i gen_rand n=10000
done

group group4 20
include_group group3
tc_manual s5
for i in {1..20}
do
tc g4-$i gen_rand n=100000000000000000000
done