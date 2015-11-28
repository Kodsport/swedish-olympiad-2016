#!/bin/bash
for a in tests/*.in; do
	echo $a
	python3 input_format_validators/validator.py < $a
	./a.out < $a | diff -U8 - ${a%.in}.ans
done

