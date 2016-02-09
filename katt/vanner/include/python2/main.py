import vanner
from sys import stdin

N, L, Q = [int(x) for x in int(stdin.readline())]
P = [int(x) for x in stdin.readline().split()]
init(N, L, P)
for i in range(Q):
    t = [int(x) for x in stdin.readline.split()]
    if t == 1:
        print(vanner.score())
    elif t == 0:
        print(vanner.jump(t[1], t[2]))
    else:
        assert False
