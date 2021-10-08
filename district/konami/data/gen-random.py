#!/usr/bin/env python3
import sys
import random

needle = "UUNNVHVHBA"
alphabet = sys.argv[1] or "UNHVBA"
n = int(sys.argv[2])
random.seed(int(sys.argv[3]))
ar = [random.choice(alphabet) for _ in range(n)]
exc = sorted(random.sample(range(n), len(needle)))
for pos, ch in zip(exc, needle):
    ar[pos] = ch

print(''.join(ar))
