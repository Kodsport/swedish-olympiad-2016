#!/bin/bash
PPATH=$(realpath ..)
. ../../../../testdata_tools/gen.sh


use_solution ../sol.cpp

compile copy.py # Arguments: testcase

g++ -O2 isconvex.cpp -o isconvex
g++ -O2 -std=c++14 genConvex.cpp -o gen-convex

./gen-convex 100000 2 >../manual/023.in # ans = 2
./gen-convex 20000 2 >../manual/024.in # ans = 1
./gen-convex 23760 2 >../manual/025.in # ans = 2
./gen-convex 23760 8 >../manual/026.in # ans = 2
./gen-convex 1000 2 >../manual/027.in # ans = 1

samplegroup 
sample 1

group 1-small 30
tc 1
tc_manual ../manual/001.in
tc_manual ../manual/002.in
tc_manual ../manual/003.in
tc_manual ../manual/004.in
tc_manual ../manual/005.in
tc_manual ../manual/006.in
tc_manual ../manual/007.in
tc_manual ../manual/008.in

group 2-convex 30
tc 008
tc_manual ../manual/023.in
tc_manual ../manual/024.in
tc_manual ../manual/025.in
tc_manual ../manual/026.in

group 3-large 40
include_group 1-small
include_group 2-convex
tc_manual ../manual/009.in
tc_manual ../manual/010.in
tc_manual ../manual/011.in
tc_manual ../manual/012.in
tc_manual ../manual/013.in
tc_manual ../manual/014.in
tc_manual ../manual/015.in
tc_manual ../manual/016.in
tc_manual ../manual/017.in
tc_manual ../manual/018.in
tc_manual ../manual/019.in
tc_manual ../manual/020.in
tc_manual ../manual/021.in
tc_manual ../manual/022.in

rm gen-convex isconvex

