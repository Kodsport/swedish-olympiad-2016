#!/usr/bin/python3
import sys
import re

line = sys.stdin.readline()
assert re.match('^[0-9]+\n$', line)
N = int(line.strip())
assert 1 <= N <= 100000

line = sys.stdin.readline()
assert re.match('^[0-9]+( [0-9]+)*\n$', line)
L = [ int(t) for t in line.strip().split(' ') ]

line = sys.stdin.readline()
assert re.match('^[0-9]+( [0-9]+)*\n$', line)
H = [ int(t) for t in line.strip().split(' ') ]

line = sys.stdin.readline()
assert re.match('^[0-9]+( [0-9]+)*\n$', line)
T = [ int(t) for t in line.strip().split(' ') ]

assert len(L) == N
assert len(H) == N
assert len(T) == N

mT = max(T)
for i in range(N):
    assert 0 <= L[i] <= H[i] <= mT
    assert 0 <= T[i] <= 10**9

assert sys.stdin.read() == ''
sys.exit(42)
