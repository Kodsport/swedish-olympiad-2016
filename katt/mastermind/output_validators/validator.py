#!/usr/bin/python3

# tester for the task "mastermind"
# usage: ./tester.py input_file correct_output output_dir < contestants_output

import os
from sys import stdin, exit, argv
import sys
import re
import random

def die(msg):
    print(msg)
    f = open(argv[3] + os.sep + "score.txt", "wt+", encoding="utf-8")
    f.write("0")
    f.close()
    exit(43)

def accept(score, real_score):
    f = open(argv[3] + os.sep + "score.txt", "wt+", encoding="utf-8")
    f.write(str(score))
    f.close()
    f = open(argv[3] + os.sep + "judgemessage.txt", "wt+", encoding="utf-8")
    f.write(str(real_score))
    f.close()
    exit(42)

def safe_print(n):
    try:
        print(n)
        sys.stdout.flush()
    except IOError:
        pass

fin, fcor = open(argv[1],'r'), open(argv[2],'r')

best = int(fcor.read())

n, case, case_score, seed = fin.read().split()
n = int(n)
case_score = int(case_score)
seed = int(seed)
assert case in ['exp', '2n', 'n', 'rel']

random.seed(seed)

def score(guesses, best):
    if case == 'exp':
        return 1 if guesses <= 2**n else 0
    if case == '2n':
        return 1 if guesses <= 2*n else 0
    if case == 'n':
        return 1 if guesses <= 2+n else 0
    if case == 'rel':
        assert guesses >= best
        return (n - guesses) / (n - best) if guesses < n else 0
    assert False, "unknown type " + case

target = ''.join(random.choice(['0', '1']) for _ in range(n))

try:
    safe_print(n)

    guesses = 0
    guess = None
    while guess != target:
        guesses += 1
        guess = stdin.readline().strip()
        if len(guess) != n:
            die("wrong length")
        if any(x != '0' and x != '1' for x in guess):
            die("invalid char in guess")
        safe_print(sum(1 for i in range(n) if guess[i] == target[i]))

    sc = score(guesses, best)
    if sc == 0:
        die("too many guesses")
    accept(case_score * sc, guesses)
except ValueError as e:
    die("parse failure: " + e)
