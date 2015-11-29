#!/bin/bash

# Set the problem name to generate correct file names
PROBLEMNAME="namnsdag"

g++ ../submissions/accepted/namnsdag_osk.cc -std=c++0x -o sol
g++ gen.cc -std=c++0x -o gen

# Set this if you want to generate answers.
SOLVER=sol

subfolders=(secret/g1 secret/g2)
for i in ${subfolders[@]}
do
    if [ ! -d $i ]
    then
        mkdir $i
    fi
done

echo "grading: custom
grader_flags: all 53" > secret/g1/testdata.yaml
echo "grading: custom
grader_flags: all 47" > secret/g2/testdata.yaml

echo "Generating group 1..."
echo "11 50 5" | ./gen > secret/g1/$PROBLEMNAME.g1.1.in
echo "12 49 5" | ./gen > secret/g1/$PROBLEMNAME.g1.2.in
echo "13 48 5" | ./gen > secret/g1/$PROBLEMNAME.g1.3.in
echo "14 47 5" | ./gen > secret/g1/$PROBLEMNAME.g1.4.in
echo "15 46 5" | ./gen > secret/g1/$PROBLEMNAME.g1.5.in
echo "16 45 5" | ./gen > secret/g1/$PROBLEMNAME.g1.6.in
echo "17 44 5" | ./gen > secret/g1/$PROBLEMNAME.g1.7.in
echo "18 1 5" | ./gen > secret/g1/$PROBLEMNAME.g1.8.in

echo "Generating group 2..."
echo "21 1 1" | ./gen > secret/g2/$PROBLEMNAME.g2.1.in
echo "22 5 10" | ./gen > secret/g2/$PROBLEMNAME.g2.2.in
echo "23 500 10" | ./gen > secret/g2/$PROBLEMNAME.g2.3.in
echo "24 5000 10" | ./gen > secret/g2/$PROBLEMNAME.g2.4.in
echo "25 10000 10" | ./gen > secret/g2/$PROBLEMNAME.g2.5.in
echo "26 10000 7" | ./gen > secret/g2/$PROBLEMNAME.g2.6.in
echo "27 10000 5" | ./gen > secret/g2/$PROBLEMNAME.g2.7.in
echo "28 10000 3" | ./gen > secret/g2/$PROBLEMNAME.g2.8.in

# generate solutions for all files
if [[ ! -z $SOLVER ]]
then
    for i in ${subfolders[@]}
    do
        for f in $i/*.in
        do
            echo "solving $f"
            ./$SOLVER < $f > ${f%???}.ans
        done
    done
fi
