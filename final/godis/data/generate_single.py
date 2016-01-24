#!/usr/bin/env python3
# Usage: python3 generate_single.py n k seed

import string
import random
import sys

(n, k, seed) = [int(s) for s in sys.argv[1:]]
random.seed(seed)

print(n)
for _ in range(n):
    tp = random.randint(1, k)
    if random.choice([True, False]):
        tp = -tp
    print('1 {} {}'.format(tp, random.randint(1, 1000)))
