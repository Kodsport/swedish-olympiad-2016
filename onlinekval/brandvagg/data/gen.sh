#!/bin/bash

PROBLEMNAME="brandvagg"
VALIDATOR=../input_format_validators/validator.py
g++ -std=c++11 -O2 ../submissions/accepted/brandvagg_js.cpp -o /tmp/sol
SOLVER=/tmp/sol

rm -rf secret
mkdir secret
echo "grading: custom
grader_flags: sum" > secret/testdata.yaml

function group {
	groupname=$1
	points=$2
	mkdir secret/$groupname
	echo "grading: custom
grader_flags: all $points" > secret/$groupname/testdata.yaml
	ind=0
	echo "Generating group $groupname..."
}

function solve {
	python3 $VALIDATOR <$1
	$SOLVER < $1 > ${1%.in}.ans
}

function testcase_manylimits {
	ind=$((ind+1))
	python3 generate_many_limits.py "$@" $ind > $in
	solve $in
}

function testcase_random {
	ind=$((ind+1))
	in=secret/$groupname/$PROBLEMNAME.$groupname.$ind.in
	echo $in
	python3 generate_random.py "$@" $ind > $in
	solve $in
}

function repeat {
	rep=$1
	shift
	for i in $(seq 1 $rep); do
		eval $@
	done
}

group g1 7
# P <= 10,000. Det finns bara accept-handlingar.

group g2 15
# P <= 10,000. Ingen regel har något villkor.

group g3 29
# P <= 10,000. Det finns inga limit-villkor.

group g4 25
# P <= 100$
repeat 2 testcase_random 100 100 10 10
testcase_random 100 100 2 2
testcase_random 100 100 30 30
testcase_manylimits 100 100

group g5 14
# P <= 1,000
repeat 2 testcase_random 100 1000 10 10
testcase_random 100 1000 2 2
testcase_random 100 1000 40 40
testcase_random 100 1000 500 500
testcase_manylimits 100 1000

group g6 10
# P <= 10,000
repeat 2 testcase_random 100 10000 10 10
testcase_random 100 10000 2 2
testcase_random 100 10000 40 40
testcase_random 100 10000 500 500
testcase_manylimits 100 10000
