#!/bin/bash

PROBLEMNAME="mastermind"

rm -rf secret
mkdir secret
cp testdata.yaml secret/

g++ -O2 isconvex.cpp -o isconvex
g++ -O2 -std=c++14 genConvex.cpp -o gen-convex
g++ -O2 -std=c++11 ../submissions/sol.cpp -o sol

./gen-convex 100000 2 >../manual/023.in # ans = 2
./gen-convex 20000 2 >../manual/024.in # ans = 1
./gen-convex 23760 2 >../manual/025.in # ans = 2
./gen-convex 23760 8 >../manual/026.in # ans = 2
./gen-convex 1000 2 >../manual/027.in # ans = 1
./sol <../manual/023.in >../manual/023.ans
./sol <../manual/024.in >../manual/024.ans
./sol <../manual/025.in >../manual/025.ans
./sol <../manual/026.in >../manual/026.ans
./sol <../manual/027.in >../manual/027.ans

# Arguments:
# groupname
# points
function group {
	groupname=$1
	points=$2
	mkdir -p secret/$groupname
	echo "grading: custom
grader_flags: all $points" > secret/$groupname/testdata.yaml
}

group g1 30
for X in ../manual/*.in; do
	Y=${X%.in}.ans
	X2=$(basename $X)
	Y2=$(basename $Y)
	n=$(head -1 $X | cut -d' ' -f1)
	echo $n
	if [[ $n -le 1000 ]]; then
		cp $X secret/g1/g1.$X2
		cp $Y secret/g1/g1.$Y2
	fi
done

group g2 30
for X in ../manual/*.in; do
	Y=${X%.in}.ans
	X2=$(basename $X)
	Y2=$(basename $Y)
	if ./isconvex < $X; then
		cp $X secret/g2/g2.$X2
		cp $Y secret/g2/g2.$Y2
	fi
done

group g3 40
for X in ../manual/*.in; do
	Y=${X%.in}.ans
	X2=$(basename $X)
	Y2=$(basename $Y)
	cp $X secret/g3/g3.$X2
	cp $Y secret/g3/g3.$Y2
done

rm gen-convex sol isconvex
