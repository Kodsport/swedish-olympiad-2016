#/usr/bin/env python
import sys
import re

sys.setrecursionlimit(101000)

class UnionFind:
    def __init__(self, n):
        self.pars = [-1 for _ in range(n)]

    def find(self, x):
        if self.pars[x] < 0:
            return x
        self.pars[x] = self.find(self.pars[x])
        return self.pars[x]

    def join(self, a, b):
        a = self.find(a)
        b = self.find(b)
        assert a != b
        if -self.pars[a] < -self.pars[b]:
            a, b = b, a
        self.pars[a] += self.pars[b]
        self.pars[b] = a

re1 = '''^(0|[1-9][0-9]*) (0|[1-9][0-9]*)$'''
line = sys.stdin.readline() 
assert re.match(re1, line)
N, P = map(int, line.split())
assert 1 <= K <= N <= 100000

re2 = '''^(0|[1-9][0-9]*)( (0|[1-9][0-9]*))*$'''
line1 = map(int, sys.stdin.readline().split(' '))
line2 = map(int, sys.stdin.readline().split(' '))
line3 = map(int, sys.stdin.readline().split(' '))
assert len(line1) == N
assert len(line2) == N-1
assert len(line3) == N-1

for i in line1: assert abs(i) < 1000000000

uf = UnionFind(N)
for i in range(N-1):
    uf.join(line2[i], line3[i])

line = sys.stdin.readline()
assert len(line) == 0
sys.exit(42)
