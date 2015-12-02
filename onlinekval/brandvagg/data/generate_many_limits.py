#!/usr/bin/env python3
# Usage: python3 generate_many_limits.py n p seed

import string
import random
import sys

(n, p, seed) = [int(s) for s in sys.argv[1:]]
random.seed(seed)

ip = '123.213.132.231'
otherip = '11.11.11.11'

print(n)
for i in range(n-4):
    lim = 1000 if i % 2 == 0 else 600
    print('accept ip={} limit={}'.format(ip, lim))
print('log')
print('accept ip={} limit=500'.format(ip))
print('drop ip={}'.format(ip))
print('drop ip={}'.format(otherip))

print(p)
i2 = 0
ip = ip + ':1'
otherip = otherip + ':2'
for i in range(p):
    if i % 1000 == 0:
        print(otherip)
    else:
        m = i2 % 4
        print(otherip if m < 2 else ip)
        i2 += 1
