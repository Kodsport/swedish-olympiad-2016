#!/bin/bash
. ../../../testdata_tools/gen.sh

use_solution simon.cpp

compile generator_random.py
compile generator_regular.py
compile generator_stair.py

samplegroup
sample sample01
sample sample02
sample sample03


group g1 19
tc sample01
tc sample02
tc sample03
tc g1-1 generator_random 10 10 10
tc g1-2 generator_random 10 10 10
tc g1-3 generator_random 10 10 10
tc g1-4 generator_random 10 100 100
tc g1-5 generator_random 10 100 100
tc g1-6 generator_random 100 100 100
tc g1-7 generator_random 100 100 100
tc g1-8 generator_random 100 100 100
tc g1-9 generator_stair 100 100 0
tc g1-10 generator_stair 99 100 1
tc g1-11 generator_stair 50 100 2
tc g1-12 generator_stair 50 100 3
tc g1-13 generator_stair 50 100 4
tc g1-14 generator_stair 30 100 5
tc_manual ../manual/manual01.in
tc_manual ../manual/manual02.in
tc_manual ../manual/manual03.in
tc_manual ../manual/manual04.in
tc_manual ../manual/manual05.in
tc_manual ../manual/manual06.in
tc_manual ../manual/manual07.in
tc_manual ../manual/manual08.in
tc_manual ../manual/manual09.in
tc_manual ../manual/manual10.in


group g2 26
include_group g1
tc g2-1 generator_stair 1000 1000 0
tc g2-2 generator_stair 500 1000 1
tc g2-3 generator_stair 500 1000 2
tc g2-4 generator_stair 500 1000 3
tc g2-5 generator_stair 500 1000 4
tc g2-6 generator_stair 500 1000 5
tc g2-7 generator_random 1000 1000 1000
tc g2-8 generator_random 1000 1000 1000
tc g2-9 generator_random 1000 1000 1000
tc g2-10 generator_random 1000 1000 1000
tc g2-11 generator_random 1000 1000 1000

group g3 17
include_group g2
tc g3-1 generator_random 1000 1000 1000
tc g3-2 generator_random 1000 1000 1000
tc g3-3 generator_random 1000 1000 1000
tc g3-4 generator_random 1000 1000 1000
tc g3-6 generator_random 1000 1000 100000
tc g3-7 generator_regular 1000 1000 100000
tc g3-8 generator_stair 1000 100000 1
tc g3-9 generator_stair 1000 100000 4
tc g3-10 generator_stair 1000 100000 5


group g4 23
include_group g3
tc g4-1 generator_random 20000 10000000 10000000
tc g4-6 generator_random 20000 10000000 10000000
tc g4-3 generator_regular 20000 10000000 10000000
tc g4-4 generator_stair 20000 10000000 4
tc g4-5 generator_stair 20000 10000000 5

group g5 15
include_group g4
tc g5-1 generator_regular 300000 10000000 1000000000000000000
tc g5-2 generator_stair 300000 1000000000000000000 0
tc g5-3 generator_stair 300000 1000000000000000000 1
tc g5-4 generator_stair 300000 1000000000000000000 2
tc g5-5 generator_stair 300000 1000000000000000000 3
tc g5-6 generator_stair 300000 1000000000000000000 4
tc g5-7 generator_stair 300000 1000000000000000000 5
tc g5-8 generator_random 300000 1000000000000000000 1000000000000000000
tc g5-9 generator_random 300000 1000000000000000000 1000000000000000000
tc g5-13 generator_random 300000 1000000000000000000 1000000000000000000
tc g5-11 generator_random 300000 1000000000000000000 1000000000000000000
tc g5-12 generator_random 300000 1000000000000000000 1000000000000000000
