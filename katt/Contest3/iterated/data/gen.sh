#!/bin/bash

PROBLEMNAME="mastermind"

rm -rf secret
mkdir secret
cp testdata.yaml secret/

# Arguments:
# groupname
# points
# case: exp, 2n, n, rel
# n
function group1 {
	groupname=$1
	points=$2
	case=$3
	n=$4
	seed=$((seed+1))
	mkdir -p secret/$groupname
	echo $n $case $points $seed > secret/$groupname/$PROBLEMNAME.$groupname.in
	echo 0 > secret/$PROBLEMNAME.$groupname.ans
}

function group2 {
	groupname=$1
	points=$2
	case=$3
	mkdir -p secret/$groupname
	echo "grading: custom
grader_flags: all $points" > secret/$groupname/testdata.yaml
}

function testcase {
	seed=$((seed+1))
	n=$1
	echo $n $case 1 $seed > secret/$groupname/$PROBLEMNAME.$groupname.in
	echo 0 > secret/$groupname/$PROBLEMNAME.$groupname.ans
}

function repeat {
    rep=$1
    shift
    for i in $(seq 1 $rep); do
        eval $@
    done
}

group2 g1 1 exp
repeat 2 testcase 10

group2 g2 1 2n
repeat 2 testcase 5000

group2 g3 1 n 5000
repeat 2 testcase 5000

group1 g4 1 rel 5000
