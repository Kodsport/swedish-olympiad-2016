#!/usr/bin/python3

import sys
n=int(sys.stdin.readline())
s=sys.stdin.readline().strip()
now=0
for i in range(n):
   m=-1
   for c in ('R','G','B'):
        k=s.find(c,now)
        assert k>=0
        m=max(m,k)
   sys.stdout.write(s[m])
   now=m+1
sys.stdout.write('\n')
