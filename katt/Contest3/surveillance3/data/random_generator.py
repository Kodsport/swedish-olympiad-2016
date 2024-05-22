#!/usr/bin/env pypy
from __future__ import print_function
import sys
import random
import math

N = int(sys.argv[1])
M = int(sys.argv[2])
lim1 = int(float(sys.argv[3]))
lim2 = int(float(sys.argv[4]))
case = sys.argv[5]
random.seed(int(sys.argv[6]))

S = [[random.randrange(lim2, lim2+lim1) for _ in range(N)] for _ in range(N)]
T = [[random.randrange(lim2, lim2+lim1) for _ in range(M)] for _ in range(M)]
for _ in range(20):
    x = random.randint(0, N - M)
    y = random.randint(0, N - M)
    delta = random.randint(-lim2, lim2)
    for i in range(M):
        S[y + i][x:x+M] = [t + delta for t in T[i]]
    lastx, lasty = x, y
if case == 'no':
    lastx += random.randrange(0, M)
    lasty += random.randrange(0, M)
    S[lasty][lastx] = random.choice(random.choice(S))

print(N, M)
for row in S: print(" ".join(map(str, row)))
for row in T: print(" ".join(map(str, row)))
