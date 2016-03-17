import sys
import random
import math

N = int(sys.argv[1])
aa = int(sys.argv[2])
random.seed(int(sys.argv[3]))

s = []
for i in range(N):
    if len(s) > i: continue
    if random.randint(0, 99) >= 10: s += ['b']
    else: s += ['a', 'b']
if len(s) > N: s.pop()

pos = set()
for i in range(N):
    if s[i] == 'b' and (s[(i - 1)%N] == 'a' or s[(i + 1)%N] == 'a'): pos.add(i)

while aa > 0 and len(pos):
    p = random.sample(pos, 1)[0]
    s[p] = 'a'
    if s[p - 1] == 'b': pos.add(p - 1)
    if s[p + 1] == 'b': pos.add((p + 1)%N)

sys.stdout.write('%d\n' % N)
sys.stdout.write('%s\n' % ''.join(s))
