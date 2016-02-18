#!/usr/bin/env python3
import sys
import random

N = int(sys.argv[1])
K = int(sys.argv[2])
case = sys.argv[3]
random.seed(int(sys.argv[4]))

nonneg = (case == 'nonneg')
two = (case == 'two')

wlim = round(K * 0.6)

totgreedy = 0 if nonneg else random.randint(1, K*2)
ngreedy = 0 if nonneg else random.randint(1, N)
wgr = random.sample(list(range(N)), ngreedy)
if ngreedy:
    greach = random.sample(list(range(ngreedy + totgreedy - 1)), ngreedy - 1)
    greach += [-1, ngreedy + totgreedy-1]
    greach.sort()
    assert len(greach) == ngreedy + 1
    res = []
    for i in range(ngreedy):
        v = greach[i+1] - greach[i] - 1
        assert v >= 0
        res.append(v)
    assert sum(res) == totgreedy
    greach = res

L = []
R = []
for i in range(N):
    l = r = None
    if i in wgr:
        g = greach[wgr.index(i)]
        if random.choice([True, False]):
            r = g
            l = -g - random.randint(1, 100000) * 2
        else:
            l = -g
            r = g + random.randint(1, 100000) * 2
        if two:
            if random.choice([True, False]):
                l, r = -1, 1
            elif random.choice([True, False]):
                l, r = 0, 2
            else:
                l, r = -2, 0
    else:
        # should cost roughly C*W to get to and have score W, for some
        # C ~ 1, and a per-case W, preferably with C*W*N >> K.
        c = random.uniform(0.8, 1.2)
        w = random.randint(1, wlim)
        cost = round(c * w)
        if two:
            w = 1
        if random.choice([True, False]) or nonneg:
            l, r = cost, cost + w*2
        else:
            l, r = -cost - w*2, -cost
    assert l <= r
    assert (l+r) % 2 == 0
    if nonneg:
        assert 0 <= l
    if two:
        assert r - l == 2
    L.append(l)
    R.append(r)

print("{} {}".format(N, K))
print(" ".join(map(str, L)))
print(" ".join(map(str, R)))
