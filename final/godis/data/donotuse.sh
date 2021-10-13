#!/bin/bash

PROBLEMNAME="godis"
g++ -std=c++11 -O2 ../submissions/accepted/godis_sl.cpp -o /tmp/sol
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
	$SOLVER < $1 > ${1%.in}.ans
}

function testcase_single {
	ind=$((ind+1))
	in=secret/$groupname/$PROBLEMNAME.$groupname.$ind.in
	echo $in
	python3 generate_single.py "$@" $ind > $in
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

group g1 25
# N <= 15
testcase_single 15 10
repeat 4 testcase_random 15 10
repeat 2 testcase_random 15 4
testcase_random 15 3

group g2 25
# N <= 1000. Every bag has just one type of candy.
repeat 3 testcase_single 1000 10

group g3 50
# N <= 1000
testcase_random 15 10
testcase_random 15 3
repeat 4 testcase_random 1000 10
repeat 2 testcase_single 1000 10
