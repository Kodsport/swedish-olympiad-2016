#/usr/bin/env python
import sys
import re

sys.setrecursionlimit(101000)

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        exit(1)
    return default


max_n = int(cmdlinearg('N'))
max_k = int(cmdlinearg('K', max_n))

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
N, K = map(int, line.split())
assert 2 <= N <= max_n
assert 1 <= K <= max_k

re2 = '''^(0|[1-9][0-9]*)( (0|[1-9][0-9]*))*$'''
line1 = map(int, sys.stdin.readline().split(' '))
line2 = map(int, sys.stdin.readline().split(' '))
assert len(line1) == N-1
assert len(line2) == N-1
uf = UnionFind(N)
for i in range(N-1):
    uf.join(line1[i], line2[i])

line = sys.stdin.readline()
assert len(line) == 0
sys.exit(42)
