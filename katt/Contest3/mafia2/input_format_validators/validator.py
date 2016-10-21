#/usr/bin/env python
import sys
import re

re2 = '''^(0|[1-9][0-9]*)( (0|[1-9][0-9]*))*$'''
line = sys.stdin.readline() 
assert re.match(re2, line)
N, M = map(int, line.split())
assert 0 <= N <= 1000
assert 0 <= M <= 1000000

A = list(map(int, sys.stdin.readline().split(' ')))
B = list(map(int, sys.stdin.readline().split(' ')))
T = list(map(int, sys.stdin.readline().split(' ')))
assert len(A) == M
assert len(B) == M
assert len(T) == M
for i, j in zip(A, B): assert i != j
for i in A: assert 0 <= i < N
for i in B: assert 0 <= i < N
for i in T: assert 1 <= i <= 2

line = sys.stdin.readline()
assert len(line) == 0
sys.exit(42)
