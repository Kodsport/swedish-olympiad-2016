#!/bin/bash

# Set the problem name to generate correct file names
PROBLEMNAME="kohagen"

g++ -O2 ../submissions/emanuel_ac.cpp -o sol
g++ -O2 generator_max.cpp -o generator_max.out

# Set this if you want to generate answers.
SOLVER=sol

# 1. Create subdirectories and set them to "min"
#    grading mode.

rm -rf secret
mkdir secret
echo "grading: custom
grader_flags: sum2" > secret/testdata.yaml

function group {
	groupname=$1
	points=$2
	mkdir secret/$groupname
	echo "grading: custom
grader_flags: all $points" > secret/$groupname/testdata.yaml
	ind=0
	echo "Generating group $groupname..."
}

function testcase_random {
	ind=$((ind+1))
	python generator_random.py "$@" $ind > secret/$groupname/$PROBLEMNAME.$groupname.$ind.in
}
function testcase_manual {
	ind=$((ind+1))
	python generator_manual.py "$@" $ind > secret/$groupname/$PROBLEMNAME.$groupname.$ind.in
}
function testcase_regular {
	ind=$((ind+1))
	python generator_regular.py "$@" $ind > secret/$groupname/$PROBLEMNAME.$groupname.$ind.in
}
function testcase_max {
	ind=$((ind+1))
	echo -n .
	echo "$@" $ind | ./generator_max.out > secret/$groupname/$PROBLEMNAME.$groupname.$ind.in
}

group g1 23
testcase_random 4 50 10 1000
testcase_random 4 50 10 1000
testcase_random 4 50 10 1000
testcase_random 4 50 10 1000
testcase_random 4 50 10 1000
testcase_manual 50 1000 1

group g2 21
testcase_regular 4 200 10 1000
testcase_regular 4 200 10 1000
testcase_regular 4 200 10 1000
testcase_regular 4 200 10 1000
testcase_regular 4 200 10 1000
testcase_regular 200 200 900 1000

group g3 34
testcase_max 142 513 360
testcase_max 160 914 360
testcase_max 74 755 360
testcase_max 200 999 360
testcase_max 200 1000 360
testcase_max 200 1000 360
testcase_max 200 1000 270
testcase_max 200 1000 270
testcase_max 200 1000 180
testcase_max 200 1000 90
echo

group g4 13
testcase_random 100 200 10 1000
testcase_random 100 200 10 1000
testcase_random 100 200 10 1000
testcase_random 100 200 10 1000
testcase_random 100 200 10 1000
testcase_manual 200 1000 1
testcase_random 200 200 900 1000

group g5 9
for i in {1..5}; do testcase_random 300 400 10 1000; done
testcase_manual 400 1000 1
for i in {1..4}; do testcase_random 400 400 10 1000; done
testcase_max 400 1000 270
testcase_max 400 1000 270
echo

# generate solutions for all files
for f in secret/g{1,2,3,4,5}/*.in; do
	echo "solving $f"
	./$SOLVER < $f > ${f%???}.ans
done
