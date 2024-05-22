#!/usr/bin/env python3
import re
import sys
from sys import stdin

def is_int(line):
    return re.match("^(0|[1-9][0-9]*)$", line) != None

def is_float(line):
    return re.match("^(0|[1-9][0-9]*)(.[0-9]+)?$", line) != None

line = stdin.readline()

assert is_int(line)

N = int(line)
assert N % 2 == 0
assert 2 <= N <= 50000

vals = []

for i in range(N):
    line = stdin.readline()
    assert is_float(line)
    angle = float(line)
    assert 0 <= angle < 360
    assert line.strip() not in [str(45*x//2) if x%2 == 0 else str(22 + 45 * (x//2)) + ".5" for x in range(16)]
    vals.append(int(angle / 22.5))

for i in range(0, N, 2):
    a = 16 * vals[i] + vals[i + 1]
    assert 32 <= a <= 126

line = stdin.readline()
assert len(line) == 0

sys.exit(42)
