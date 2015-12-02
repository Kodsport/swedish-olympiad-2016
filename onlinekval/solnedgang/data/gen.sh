#!/bin/bash
set -e

# Set the problem name to generate correct file names
PROBLEMNAME="solnedgang"

g++ -std=c++11 -O2 ../submissions/accepted/aron.cpp -o /tmp/sol

# Set this if you want to generate answers.
SOLVER=/tmp/sol
VALIDATOR=../input_format_validators/validator.py

# 1. Create subdirectories and set them to "min"
#    grading mode.

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

function testcase_random {
	printf '*'
	ind=$((ind+1))
	python3 generator_random.py "$@" $ind $SOLVER > secret/$groupname/$PROBLEMNAME.$groupname.$ind.in
}
function testcase_manual {
	printf '*'
	ind=$((ind+1))
	cp $1.in secret/$groupname/$PROBLEMNAME.$groupname.$ind.in
	cp $1.ans secret/$groupname/$PROBLEMNAME.$groupname.$ind.ans
}
function testcase_regular {
	printf '*'
	ind=$((ind+1))
	python3 generator_regular.py "$@" $ind $SOLVER > secret/$groupname/$PROBLEMNAME.$groupname.$ind.in
}
function testcase_stair {
	printf '*'
	ind=$((ind+1))
	python3 generator_stair.py "$@" $ind $SOLVER > secret/$groupname/$PROBLEMNAME.$groupname.$ind.in
}

# generate solutions for all files
function solve_and_verify {
	printf '\n'
	for f in secret/$groupname/*.in; do
		echo "Solving $f"
		set +e
		python3 $VALIDATOR $1 $2 $3 < $f
		if [ $? -ne 42 ]; then
			echo "Validator failed"
			exit 1
		fi
		set -e
		$SOLVER < $f > ${f%???}.ans2
		set +e

		# Make sure that if this was a manual test case
		# and thus a .ans file already exists
		# then the solver should generate the same answer
		if [ -e ${f%???}.ans ]; then
			diff ${f%???}.ans ${f%???}.ans2
			if [ $? -ne 0 ]; then
				echo "Failed on manual test case"
				exit 1
			fi
		else
			mv ${f%???}.ans2 ${f%???}.ans
		fi
		set -e
	done
	printf '\n'
}


group g1 19
# 19
testcase_random 10 10 10 -1
testcase_random 10 10 10 5
testcase_random 10 10 10 2
testcase_random 10 100 100 0
testcase_random 10 100 100 0
testcase_random 100 100 100 0
testcase_random 100 100 100 0
testcase_random 100 100 100 0
testcase_stair 100 100 0 0
testcase_stair 99 100 1 0
testcase_stair 50 100 2 0
testcase_stair 50 100 3 0
testcase_stair 50 100 4 0
testcase_stair 30 100 5 0

# Edge cases
for i in ../manual/*.in; do testcase_manual ${i%???}; done

# n, k <= 100, h, w <= 100
solve_and_verify 100 100 100


group g2 26
# 45
testcase_stair 1000 1000 0 0
testcase_stair 500 1000 1 0
testcase_stair 500 1000 2 0
testcase_stair 500 1000 3 0
testcase_stair 500 1000 4 0
testcase_stair 500 1000 5 0
for i in {1..5}; do testcase_random 1000 1000 1000 0; done

# Edge cases
for i in ../manual/*.in; do testcase_manual ${i%???}; done

# n, k, h, w <= 1000
solve_and_verify 1000 1000 1000


group g3 17
# 62
testcase_random 1000 1000 1000 0
testcase_random 1000 1000 1000 0
testcase_random 1000 1000 1000 0
testcase_random 1000 1000 1000 0
testcase_random 1000 1000 100000 0
testcase_regular 1000 1000 100000 0

# Edge cases
for i in ../manual/*.in; do testcase_manual ${i%???}; done

testcase_stair 1000 100000 1 0
testcase_stair 1000 100000 4 0
testcase_stair 1000 100000 5 0

# k, n <= 1000, h, w <= 100000
solve_and_verify 1000 1000 100000


group g4 23
# 85
testcase_random 20000 10000000 10000000 0
testcase_random 20000 10000000 10000000 0
testcase_regular 20000 10000000 10000000 0
testcase_stair 20000 10000000 4 0
testcase_stair 20000 10000000 5 0

# Edge cases
for i in ../manual/*.in; do testcase_manual ${i%???}; done

# n <= 20000, k, h, w <= 10^7
solve_and_verify 20000 10000000 10000000


group g5 15
# 100
testcase_regular 300000 10000000 1000000000000000000 0
for i in {1..5}; do testcase_random 300000 1000000000000000000 1000000000000000000 0; done
testcase_stair 300000 1000000000000000000 0 0
testcase_stair 300000 1000000000000000000 1 0
testcase_stair 300000 1000000000000000000 2 0
testcase_stair 300000 1000000000000000000 3 0
testcase_stair 300000 1000000000000000000 4 0
testcase_stair 300000 1000000000000000000 5 0

# Edge cases
for i in ../manual/*.in; do testcase_manual ${i%???}; done

# n <= 300000, k, h, w <= 10^18
solve_and_verify 300000 1000000000000000000 1000000000000000000
