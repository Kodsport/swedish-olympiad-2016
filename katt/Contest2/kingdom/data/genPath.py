from __future__ import print_function
from __future__ import division
import random
import math
import sys

N = int(sys.argv[1])
each = int(sys.argv[2])
random.seed(int(sys.argv[3]))

distr = [1, 1, 1, 1, 0, 0, -1, -2]

cur = 0
target = None
targetd = None
time = 0
parts = 0
ret = []
for x in range(N):
    if time == 0:
        targetd = random.choice(distr)
        target = each * targetd
        time = random.randint(1, min(N - x, 3))
    time -= 1
    if time == 0:
        ret.append(target - cur)
        cur = 0
        parts += targetd
    else:
        v = random.randint(-abs(each), abs(each))
        ret.append(v)
        cur += v

print(N, parts)
print(" ".join(map(str, ret)))
print(" ".join(str(i) for i in range(N-1)))
print(" ".join(str(i+1) for i in range(N-1)))
