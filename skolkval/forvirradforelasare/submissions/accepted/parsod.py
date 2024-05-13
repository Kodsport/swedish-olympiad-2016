#!/usr/bin/python3

import sys
f=list(map(int,sys.stdin.read().split()[1:]))
print(sum([max(x-y,0) for x,y in zip(f,f[1:])]), sum([max(y-x,0) for x,y in zip(f,f[1:])]))
