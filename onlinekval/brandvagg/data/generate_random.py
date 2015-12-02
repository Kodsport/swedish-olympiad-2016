#!/usr/bin/env python3
# Usage: python3 generate_random.py n p ips ports type seed

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

maxlim = min(1000, p)
print(n)
for i in range(n-1):
    cmd = random.choice(['log']*10 + ['accept', 'accept', 'drop'])
    if tp == 1:
        cmd = 'accept'
    if tp == 2:
        print(cmd)
        continue
    q = []
    if random.choice([0,1,1]):
        q.append(' ip=' + str(random.choice(ips)))
    if random.choice([0,1,1]) or (cmd != "log" and not q):
        q.append(' port=' + str(random.choice(ports)))
    if random.choice([0,1,1]) and tp != 3:
        q.append(' limit=' + str(random.randint(1, maxlim)))
    random.shuffle(q)
    print(cmd + ''.join(q))
print('accept' if tp == 1 else 'drop')

print(p)
for i in range(p):
    print('{}:{}'.format(random.choice(ips), random.choice(ports)))
