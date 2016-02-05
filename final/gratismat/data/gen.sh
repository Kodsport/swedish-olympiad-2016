#!/bin/bash

PROBLEMNAME="gratismat"
g++ -std=c++11 -O2 ../submissions/accepted/emanuel100p.cpp -o /tmp/sol
g++ -std=c++11 -O2 randomGenerator.cpp -o randomGenerator.out
g++ -std=c++11 -O2 longChainGenerator.cpp -o longChainGenerator.out
g++ -std=c++11 -O2 completeGenerator.cpp -o completeGenerator.out
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

function testcase_random {
	ind=$((ind+1))
	in=secret/$groupname/$PROBLEMNAME.$groupname.$ind.in
	echo $in
	./randomGenerator.out "$@" $ind > $in
	solve $in
}

function testcase_long {
	ind=$((ind+1))
	in=secret/$groupname/$PROBLEMNAME.$groupname.$ind.in
	echo $in
	./longChainGenerator.out "$@" $ind > $in
	solve $in
}

function testcase_complete {
	ind=$((ind+1))
	in=secret/$groupname/$PROBLEMNAME.$groupname.$ind.in
	echo $in
	./completeGenerator.out "$@" $ind > $in
	solve $in
}

function repeat {
	rep=$1
	shift
	for i in $(seq 1 $rep); do
		eval $@
	done
}

group g1 49
# N <= 2000
testcase_random 16 8
testcase_complete 15 4
testcase_long 2000
testcase_complete 2000 100
testcase_complete 2000 1000
testcase_random 2000 10
testcase_random 2000 100
testcase_random 2000 1000
testcase_random 2000 2000

group g2 51
# N <= 100000
testcase_long 100000
testcase_complete 100000 1000
testcase_complete 100000 10000
testcase_random 100000 100
testcase_random 100000 1000
testcase_random 100000 10000
testcase_random 100000 50000
