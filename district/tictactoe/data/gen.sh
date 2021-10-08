#!/bin/bash

PROBLEMNAME="tictactoe"

rm -rf secret
mkdir secret
cp testdata.yaml secret/

# Arguments:
# groupname
# points
# case: 0 (-), 1 (never lose), 2 (win if possible), 3 (1+2)
# rands: number of cases where opponent plays randomly (gets multiplied by two to cover both going first and second)
# opts: number of cases where opponent plays optimally (likewise)
function group {
	groupname=$1
	points=$2
	case=$3
	rands=$4
	opts=$5
	mkdir secret/$groupname
	echo "grading: custom
grader_flags: all $points" > secret/$groupname/testdata.yaml
	ind=0
	for i in $(seq 1 $rands); do testcase 0 0; testcase 1 0; done
	for i in $(seq 1 $opts); do testcase 0 1; testcase 1 1; done
}

function testcase {
	ind=$((ind+1))
	sind=$(printf "%02d" $ind)
	echo $case $1 $2 $ind > secret/$groupname/$PROBLEMNAME.$groupname.$sind.in
	touch secret/$groupname/$PROBLEMNAME.$groupname.$sind.ans
}

group g1 13 0 3 2
group g2 19 1 0 5
group g3 24 2 7 0
group g4 14 3 5 3
