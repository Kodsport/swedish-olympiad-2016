import sys
import random
import math

N = int(sys.argv[1])
Pa = int(sys.argv[2])
random.seed(int(sys.argv[3]))

s = []
for i in range(N):
    if len(s) > i: continue
    if random.randint(0, 99) >= Pa: s += ['b']
    else: s += ['a']
if len(s) > N: s.pop()

sys.stdout.write('%d\n' % N)
sys.stdout.write('%s\n' % ''.join(s))
