import sys
import random

N = int(sys.argv[1])
ndistinct = int(sys.argv[2])
case = sys.argv[3]
random.seed(int(sys.argv[4]))

maxdig = 0 if case == 'zeroes' else 9

strs = [[random.randint(0, maxdig) for _ in range(6)] for _ in range(ndistinct)]

print("%d" % N)

for _ in range(N):
    s = random.choice(strs)
    if case != 'known':
        s = [random.choice([c, -1]) for c in s]
    print(' '.join(map(str, s)))
