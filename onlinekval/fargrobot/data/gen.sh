#!/bin/bash

# Set the problem name to generate correct file names
PROBLEMNAME="fargrobot"

g++ ../submissions/accepted/fargrobot.c -o sol

# Set this if you want to generate answers.
SOLVER=sol

subfolders=(secret/g1 secret/g2 secret/g3 secret/g4)
for i in ${subfolders[@]}
do
    if [ ! -d $i ]
    then
        mkdir $i
    fi
done

echo "grading: custom
grader_flags: all 20" > secret/g1/testdata.yaml
echo "grading: custom
grader_flags: all 30" > secret/g2/testdata.yaml
echo "grading: custom
grader_flags: all 20" > secret/g3/testdata.yaml
echo "grading: custom
grader_flags: all 30" > secret/g4/testdata.yaml

echo "Generating group 1..."
echo "4
RGBGGBGRBRBRGRGRB" >secret/g1/$PROBLEMNAME.g1.1.in

echo "Generating group 2..."
./gen_testcase.py 1 0.33 0.33 10 0 > secret/g2/$PROBLEMNAME.g2.1.in
./gen_testcase.py 1 0.01 0.02 100 1 > secret/g2/$PROBLEMNAME.g2.2.in
./gen_testcase.py 2 0.33 0.33 50 2 > secret/g2/$PROBLEMNAME.g2.3.in
./gen_testcase.py 2 0.02 0.45 100 3 > secret/g2/$PROBLEMNAME.g2.4.in
./gen_testcase.py 3 0.33 0.33 50 4 > secret/g2/$PROBLEMNAME.g2.5.in
./gen_testcase.py 3 0.10 0.50 100 5 > secret/g2/$PROBLEMNAME.g2.6.in
./gen_testcase.py 4 0.33 0.33 50 6 > secret/g2/$PROBLEMNAME.g2.7.in
./gen_testcase.py 4 0.20 0.30 100 7 > secret/g2/$PROBLEMNAME.g2.8.in

echo "Generating group 3..."
./gen_testcase.py 5 0.33 0.33 100 8 > secret/g3/$PROBLEMNAME.g3.1.in
./gen_testcase.py 7 0.05 0.40 200 9 > secret/g3/$PROBLEMNAME.g3.2.in
./gen_testcase.py 10 0.33 0.33 100 10 > secret/g3/$PROBLEMNAME.g3.3.in
./gen_testcase.py 10 0.20 0.20 200 11 > secret/g3/$PROBLEMNAME.g3.4.in
./gen_testcase.py 10 0.10 0.45 200 12 > secret/g3/$PROBLEMNAME.g3.5.in
./gen_testcase.py 10 0.08 0.20 200 13 > secret/g3/$PROBLEMNAME.g3.6.in

echo "Generating group 4..."
./gen_testcase.py 20 0.33 0.33 200 14 > secret/g4/$PROBLEMNAME.g4.1.in
./gen_testcase.py 20 0.10 0.45 200 15 > secret/g4/$PROBLEMNAME.g4.2.in
./gen_testcase.py 25 0.33 0.33 200 16 > secret/g4/$PROBLEMNAME.g4.3.in
./gen_testcase.py 25 0.20 0.20 200 17 > secret/g4/$PROBLEMNAME.g4.4.in
./gen_testcase.py 25 0.10 0.40 200 18 > secret/g4/$PROBLEMNAME.g4.5.in

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
