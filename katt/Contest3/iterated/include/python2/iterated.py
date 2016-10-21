#!/usr/bin/env python2
import stub

def init(n):
    g = [False] * n
    cor = stub.guess(g)
    for i in range(n):
        g[i] = 1
        cor2 = stub.guess(g)
        if cor2 < cor: g[i] = 0
        else: cor = cor2
