#!/usr/bin/python3
import regskylt
from sys import stdin

N = int(stdin.readline())
for i in range(N):
    t = [int(x) for x in stdin.readline().split()]
    print(regskylt.plate(t))
