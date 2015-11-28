#!/bin/bash
for acc in submissions/accepted/*.cpp; do
	set -e
	g++ -O2 -std=c++11 $acc -o /tmp/solnedgang_ac
	set +e
	echo "Testing $acc"
	for a in tests/*.in; do
		echo $a
		python3 input_format_validators/validator.py < $a
		set -e
		/tmp/solnedgang_ac < $a | diff -U8 - ${a%.in}.ans
		set +e
	done
done

