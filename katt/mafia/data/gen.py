#!/usr/bin/env pypy
from __future__ import print_function
from __future__ import division
import random
import math
import sys

class UnionFind:
    def __init__(self, n):
        self.pars = [-1 for _ in range(n)]

    def find(self, x):
        if self.pars[x] < 0:
            return x
        self.pars[x] = self.find(self.pars[x])
        return self.pars[x]

    def size(self, x):
        return -self.pars[self.find(x)]

    def join(self, a, b):
        a = self.find(a)
        b = self.find(b)
        if a != b:
            if -self.pars[a] < -self.pars[b]:
                a, b = b, a
            self.pars[a] += self.pars[b]
            self.pars[b] = a

ncomps = int(sys.argv[1])
N = int(sys.argv[2])
M = int(sys.argv[3])
Q = int(sys.argv[4])
random.seed(int(sys.argv[5]))
assert ncomps < N

def nonneg_partition(n, k):
    sam = random.sample(list(range(n + k - 1)), k - 1)
    sam.append(-1)
    sam.sort()
    sam.append(n + k - 1)
    return [x - y - 1 for (x, y) in zip(sam[1:], sam[:-1])]

def pos_partition(n, k):
    return [x + 1 for x in nonneg_partition(n - k, k)]

totcomps = []
toteds = []
def gen(inds, ned):
    n = len(inds)
    left = random.randint(0, n)
    right = n - left
    cl = [0] * left + [1] * right
    random.shuffle(cl)
    while True:
        ed = []
        uf = UnionFind(n)
        for i in range(ned + n - 1):
            a = random.randint(0, n-1)
            b = random.randint(0, n-1)
            if a != b:
                uf.join(a, b)
                ed.append((a, b))
        if uf.size(0) == n:
            break
    totcomps.append((left, right))
    for (a, b) in ed:
        c = 1 if cl[a] == cl[b] else 2
        toteds.append((inds[a], inds[b], c))

free_ed = M - (N - ncomps)

parts = pos_partition(N, ncomps)
ed_part = nonneg_partition(free_ed, ncomps)

ind = 0
res = []
for p in parts:
    res += [ind] * p
    ind += 1
random.shuffle(res)
parts2 = [[] for _ in parts]
for i, v in enumerate(res):
    parts2[v].append(i)

for i in range(ncomps):
    gen(parts2[i], ed_part[i])

print(N, len(toteds))
A, B, C = [], [], []
for (a, b, c) in toteds:
    A.append(a)
    B.append(b)
    C.append(c)
print(" ".join(map(str, A)))
print(" ".join(map(str, B)))
print(" ".join(map(str, C)))

print(Q)
large = (ncomps > 60)
mi = sum(min(a, b) for (a, b) in totcomps)
ma = sum(max(a, b) for (a, b) in totcomps)
args = []
for _ in range(Q):
    val = 0
    for (a, b) in totcomps:
        val += random.choice([a, b])
    if large:
        val = mi + random.randint(0, 6)
    elif random.choice([True, False]):
        val += 1
    args.append(min(val, N))
print(" ".join(map(str, args)))
