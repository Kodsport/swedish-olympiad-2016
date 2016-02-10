#!/usr/bin/env python2
import grader

def init(n):
    g = [False] * n
    cor = grader.guess(g)
    for i in range(n):
        g[i] = 1
        cor2 = grader.guess(g)
        if cor2 < cor: g[i] = 0
        else: cor = cor2
