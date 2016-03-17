#!/usr/bin/env pypy
from __future__ import print_function
from __future__ import division
import random
import math
import sys

N = int(sys.argv[1])
M = int(sys.argv[2])
E = int(sys.argv[3])
random.seed(int(sys.argv[4]))

left = random.randint(0, N)
right = N - left
cl = [0] * left + [1] * right
random.shuffle(cl)
ed = []
for i in range(M):
    a = b = 0
    while a == b:
        a = random.randint(0, N-1)
        b = random.randint(0, N-1)
    c = 1 if cl[a] == cl[b] else 2
    ed.append([a, b, c])
for e in random.sample(ed, E):
    e[2] = 3 - e[2]

print(N, M)
print(M)
A, B, C = [], [], []
for (a, b, c) in ed:
    A.append(a)
    B.append(b)
    C.append(c)
print(" ".join(map(str, A)))
print(" ".join(map(str, B)))
print(" ".join(map(str, C)))
