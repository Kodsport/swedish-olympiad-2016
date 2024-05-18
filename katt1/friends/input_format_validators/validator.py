#!/usr/bin/python3
import sys
import re

int_re = "^(0|[1-9][0-9]*)$"
intspace_re = "^(0|[1-9][0-9]*)( (0|[1-9][0-9]*))*$"

line = sys.stdin.readline() 
assert re.match(intspace_re, line)
N, L, Q = list(map(int, line.split()))
assert 1 <= N <= 100000
assert N <= L <= 1000000000
assert 0 <= Q <= 200000

line = sys.stdin.readline() 
P = list(map(int, line.split()))
has = set()
for i in P:
    assert 0 <= i < L
    assert i not in has
    has.add(i)
assert len(has) == N

for i in range(Q):
    line = sys.stdin.readline()
    assert re.match(intspace_re, line)
    par = list(map(int, line.split()))
    if par[0] == 1: assert len(par) == 1
    elif par[0] == 0:
        assert len(par) == 3
        a = par[1]
        b = par[2]
        assert 0 <= a < L
        assert 0 <= b < L

        assert a in has
        assert b not in has

        has.add(b)
        has.remove(a)
    else: assert False

line = sys.stdin.readline()
assert len(line) == 0
sys.exit(42)
