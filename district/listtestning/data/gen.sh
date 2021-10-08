#!/bin/bash

PROBLEMNAME="listtestning"

rm -rf secret
mkdir secret
# cp testdata.yaml secret/

for i in {1..10}; do
	ind=$(printf "%02d" $i)
	echo $i > secret/$PROBLEMNAME.$ind.in
	touch secret/$PROBLEMNAME.$ind.ans
done
