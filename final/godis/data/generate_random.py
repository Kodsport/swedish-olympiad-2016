#!/usr/bin/env python3
# Usage: python3 generate_random.py n k seed

import string
import random
import sys

(n, k, seed) = [int(s) for s in sys.argv[1:]]
random.seed(seed)

print(n)
for _ in range(n):
    s = str(k)
    for i in range(1, k+1):
        tp = i if random.choice([True, False]) else -i
        s += " {} {}".format(tp, random.randint(1, 1000))
    print(s)
