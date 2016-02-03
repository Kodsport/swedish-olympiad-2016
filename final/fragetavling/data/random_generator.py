#!/usr/bin/env python3
import sys
import random

n, m, k = map(int, sys.argv[1:4])
bval = sys.argv[4]
seed = int(sys.argv[5])
assert 1 <= k <= n
assert 1 <= m <= n

random.seed(seed)

lo, hi = 1, 1000

# Given an even distribution, to get a B that weighs up for having to answer a
# few suboptimal questions, we roughly have the equation:
# span / 2 + b / (n/m) = (2-k/m) * span / 2
# Compute b using by this equation, and add in a scaling factor that tells us
# how important it should be to answer all questions in some category.
if '.' in bval:
    fact = float(bval)
    b = round((1 - k/n)/2 * (hi - lo) * n / m * fact)
    b = max(min(b, 100000), 1)
else:
    b = int(bval)

print(n, m, k, b)
ent = []
for i in range(m):
    ent.append((random.randint(lo, hi), i+1))
for i in range(n-m):
    ent.append((random.randint(lo, hi), random.randint(1, m)))
for (a, b) in ent:
    print(a, b)
