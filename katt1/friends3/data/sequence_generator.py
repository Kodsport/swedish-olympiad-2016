import sys
import random


N = int(sys.argv[1])
L = int(sys.argv[2])
S = int(sys.argv[3])
J = int(sys.argv[4])

print("%d %d %d" % (N, L, S + J))
S -= 1

old = [i for i in range(N)]
random.shuffle(old)

pos = [i for i in range(N)]
poss = set(pos)
posss = {}
for i, v in enumerate(pos): posss[v] = i

lo = max(0, L - N - 500)
target = [] 
for i in range(lo, L):
    if i not in poss: target.append(i)

print(' '.join(str(x) for x in pos))
queries = [1] * S + [0] * J
random.shuffle(queries)
queries += [1]

for i in range(len(queries)):
    qtype = queries[i]
    if qtype == 1: print("1")
    else:
        if old:
            A = old.pop()
        else:
            A = random.choice(pos)
        b = random.randint(0, len(target) -1)
        B = target[b]
        target[b] = target[-1]
        target.pop()
        while B in poss:
            B = B - 1
            if B == -1:
                B = L - 1
        if A >= lo:
            a = random.randint(0, len(target) -1)
            target.append(target[a])
            target[a] = A

        pos[posss[A]] = B
        poss.remove(A)
        poss.add(B)
        posss[B] = posss[A]
        print("0 %d %d" % (A, B))
