#!/bin/bash
for acc in submissions/accepted/*.cc; do
	set -e
	g++ -O2 -std=c++11 $acc -o /tmp/solnedgang_ac
	set +e
	echo "Testing $acc"
	for a in data/sample/*.in; do
		echo $a
		python3 input_format_validators/validator.py < $a
		set -e
		/tmp/solnedgang_ac < $a | diff -U8 - ${a%.in}.ans
		set +e
	done
done

for acc in submissions/accepted/*.py; do
	echo "Testing $acc"
	for a in data/sample/*.in; do
		echo $a
		python3 input_format_validators/validator.py < $a
		set -e
		python3 $acc < $a | diff -U8 - ${a%.in}.ans
		set +e
	done
done

