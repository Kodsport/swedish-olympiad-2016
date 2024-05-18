#!/usr/bin/python3
import friends
from sys import stdin

N, L, Q = [int(x) for x in stdin.readline().split()]
P = [int(x) for x in stdin.readline().split()]
friends.init(N, L, P)
for i in range(Q):
    t = [int(x) for x in stdin.readline().split()]
    if t[0] == 1:
        print(friends.score())
    elif t[0] == 0:
        friends.jump(t[1], t[2])
    else:
        assert False
