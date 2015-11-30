#!/bin/bash
set -e

# Set the problem name to generate correct file names
PROBLEMNAME="solnedgang"

g++ -std=c++11 -O2 ../submissions/accepted/aron.cpp -o /tmp/sol
# g++ -O2 generator_max.cpp -o generator_max.out

# Set this if you want to generate answers.
SOLVER=/tmp/sol
VALIDATOR=../input_format_validators/validator.py

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
	python3 generator_random.py "$@" $ind $SOLVER > secret/$groupname/$PROBLEMNAME.$groupname.$ind.in
}
function testcase_manual {
	ind=$((ind+1))
	python3 generator_manual.py "$@" $ind $SOLVER > secret/$groupname/$PROBLEMNAME.$groupname.$ind.in
}
function testcase_regular {
	ind=$((ind+1))
	python3 generator_regular.py "$@" $ind $SOLVER > secret/$groupname/$PROBLEMNAME.$groupname.$ind.in
}

group g1 23
testcase_random 10 10 -1
testcase_random 10 10 5
testcase_random 10 10 2
testcase_random 10 100 0
testcase_random 10 100 0
testcase_random 100 100 0
testcase_random 100 100 0
testcase_random 100 100 0

group g2 21
for i in {1..10}; do testcase_random 1000 1000 0; done

group g3 21
for i in {1..10}; do testcase_random 100000 100000 0; done

group g4 21
testcase_regular 10 10 0
testcase_regular 200000 400000 0

# generate solutions for all files
for f in secret/*/*.in; do
	echo "Solving $f"
	set +e
	python3 $VALIDATOR < $f
	set -e
	$SOLVER < $f > ${f%???}.ans

done
