import sys
import random
import math

N = int(sys.argv[1])
Pa = int(sys.argv[2])
aa = int(sys.argv[3])
random.seed(int(sys.argv[4]))

s = []
for i in range(N):
    if len(s) > i: continue
    if random.randint(0, 100) > Pa: s += ['b']
    else: s += ['a', 'b']
if len(s) > N: s.pop()

pos = set()
for i in range(N):
    if s[i] == 'b' and (s[(i - 1)%N] == 'a' or s[(i + 1)%N] == 'a'): pos.add(i)

while aa > 0 and len(pos):
    p = random.sample(pos, 1)[0]
    pos.remove(p)
    aa -= 1
    s[p] = 'a'
    if s[p - 1] == 'b': pos.add(p - 1)
    if s[(p + 1)%N] == 'b': pos.add((p + 1)%N)

sys.stdout.write('%d\n' % N)
sys.stdout.write('%s\n' % ''.join(s))
