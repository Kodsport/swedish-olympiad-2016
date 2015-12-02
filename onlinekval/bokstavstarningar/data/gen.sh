#!/bin/bash

PROBLEMNAME="bokstavstarningar"
VALIDATOR=../input_format_validators/validator.py

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

function testcase {
	rep=$1
	shift
	for i in $(seq 1 $rep); do
		ind=$((ind+1))
		base=secret/$groupname/$PROBLEMNAME.$groupname.$ind
		echo $base
		python3 generator_random.py "$@" $ind >$base.in 2>$base.ans
		python3 $VALIDATOR <$base.in
	done
}

group g1 9
testcase 2 4 2 100
testcase 2 3 2 100

group g2 9
testcase 2 5 6 100
testcase 1 4 5 100
testcase 1 5 2 100

group g3 12
testcase 2 6 20 1000
testcase 1 6 10 1000
testcase 1 6 3 1000

group g4 14
testcase 2 6 15 10000
testcase 1 6 10 10000
testcase 1 6 3 10000

group g5 21
testcase 2 6 20 100000
testcase 1 6 10 100000
testcase 1 6 3 100000

group g6 35
testcase 2 13 10 500
testcase 2 6 10 500
testcase 2 6 3 500
testcase 2 13 3 500
