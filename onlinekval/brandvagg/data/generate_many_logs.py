#!/usr/bin/env python3
# Usage: python3 generate_many_logs.py n p ips ports type seed

import string
import random
import sys

(n, p, ips, ports, tp, seed) = [int(s) for s in sys.argv[1:]]
random.seed(seed)

def randip():
    return '.'.join(str(random.randrange(256)) for _ in range(4))
ips = [randip() for _ in range(ips)]
assert len(set(ips)) == len(ips)

ports = random.sample(list(range(65536)), ports)

print(n)
for i in range(n-1):
    print('log')
print('accept' if tp == 1 else 'drop')

print(p)
for i in range(p):
    print('{}:{}'.format(random.choice(ips), random.choice(ports)))
