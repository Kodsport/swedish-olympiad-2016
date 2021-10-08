#!/usr/bin/python3

# tester for the task "ratta fel"
# usage: ./tester.py input_file correct_output output_dir score < contestants_output

import os
from sys import stdin, exit, argv
import sys
import re

def die(msg):
    print(argv[3] + os.sep + "score.txt", file=sys.stderr)
    f = open(argv[3] + os.sep + "score.txt", "wt+", encoding="utf-8")
    f.write("0")
    f.close()
    exit(43)

def accept(score):
    print(argv[3] + os.sep + "score.txt", file=sys.stderr)
    f = open(argv[3] + os.sep + "score.txt", "wt+", encoding="utf-8")
    f.write(str(score))
    f.close()
    exit(42)

fin, fcor, fhis = open(argv[1],'r'), open(argv[2],'r'), stdin
from fractions import Fraction

in_text = fin.read().replace("\n", "")
try:
    team_text = fhis.read().replace("\n", "")
except UnicodeDecodeError:
    die("not valid encoding")
correct = fcor.read().replace("\n", "")

assert len(correct) == len(in_text)

if len(team_text) != len(in_text):
    die("Bad length")

errors = sum(1 if x is '#' else 0 for x in in_text)

def judge(a,b,c):
    if a == '#':
        return 1 if b == c else 0
    else:
        if a != b:
            die("changed a non-error char")
        return 0

score = sum(judge(a, b, c) for a, b, c in zip(in_text, team_text, correct))

case_score = 0 if correct.startswith("MARLEY") else 60

accept(case_score * score / errors)
