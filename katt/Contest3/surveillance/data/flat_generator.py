#!/usr/bin/env pypy
from __future__ import print_function
import sys
import random
import math

N = int(sys.argv[1])
M = int(sys.argv[2])
K1 = int(sys.argv[3])
K2 = int(sys.argv[4])
I1 = int(sys.argv[5])
I2 = int(sys.argv[6])
random.seed(int(sys.argv[7]))

S = [[0] * N for _ in range(N)]
T = [[0] * M for _ in range(M)]
for _ in range(K1):
    x = random.randrange(N)
    y = random.randrange(N)
    S[y][x] = 1
for _ in range(K2):
    x = random.randrange(M)
    y = random.randrange(M)
    T[y][x] = 1

S = [[I1^x for x in row] for row in S]
T = [[I2^x for x in row] for row in T]
print(N, M)
for row in S: print(" ".join(map(str, row)))
for row in T: print(" ".join(map(str, row)))
