#!/usr/bin/env python3
import sys
import random

n, m, k, score, b, seed = map(int, sys.argv[1:])
assert 1 <= k <= n
assert 1 <= m <= n

random.seed(seed)

print(n, m, k, b)
ent = []
for i in range(m):
    ent.append((score, i+1))
for i in range(n-m):
    ent.append((score, random.randint(1, m)))
for (a, b) in ent:
    print(a, b)
