import sys
import random


N = int(sys.argv[1])
L = int(sys.argv[2])
S = int(sys.argv[3])
J = int(sys.argv[4])
random.seed(int(sys.argv[5]))

print("%d %d %d" % (N, L, S + J))

pos = list(random.sample(range(L), N))
poss = set(pos)
posss = {}
for i, v in enumerate(pos): posss[v] = i

print(' '.join(str(x) for x in pos))
queries = [1] * S + [0] * J
random.shuffle(queries)

for i in range(S + J):
    qtype = queries[i]
    if qtype == 1: print("1")
    else:
        A = random.choice(pos)
        B = random.choice(pos)
        while B in poss:
            B = B + 1
            if B == L:
                B = 0

        pos[posss[A]] = B
        poss.remove(A)
        poss.add(B)
        posss[B] = posss[A]
        print("0 %d %d" % (A, B))
