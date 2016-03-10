#/usr/bin/env python
import sys
import re

sys.setrecursionlimit(101000)

re2 = '''^(0|[1-9][0-9]*)( (0|[1-9][0-9]*))*$'''
line = sys.stdin.readline() 
assert re.match(re2, line)
K, M = map(int, line.split())
assert K <= 100000
assert 2 <= M <= 1000000000

S = list(map(int, sys.stdin.readline().split(' ')))
assert len(S) == K
for i in S: assert 0 <= i < K

N = int(sys.stdin.readline())
assert N <= 100000
I = list(map(int, sys.stdin.readline().split(' ')))
assert len(I) == N
for i in I: assert 0 <= i < K

line = sys.stdin.readline()
assert len(line) == 0
sys.exit(42)
