#!/bin/bash
for a in tests/*.in; do
	echo $a
	./a.out < $a | diff -U8 - ${a%.in}.ans
done

