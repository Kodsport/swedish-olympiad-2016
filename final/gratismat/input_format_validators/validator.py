#/usr/bin/env python
import sys
import re

sys.setrecursionlimit(101000)

re1 = '''^(0|[1-9][0-9]*) (0|[1-9][0-9]*)$'''
line = sys.stdin.readline() 
assert re.match(re1, line)
N, M = map(int, line.split())
assert 2 <= N <= 100000
assert 1 <= M <= N

re2 = '''^(0|[1-9][0-9]*)( (0|[1-9][0-9]*))*$'''
line = sys.stdin.readline()
assert re.match(re2, line)
par = list(map(int, line.split()))	
assert len(par) == N	
zeroCount = 0;
for p in par:
	assert 0 <= p <= N	
	if p == 0:
		zeroCount += 1
assert zeroCount == 1

def dfs(i, ch):
	ret = 1
	for j in ch[i]:
		ret += dfs(j, ch)
	return ret

ch = [[] for i in range(N+1)]
for i in range(N):
	ch[par[i]].append(i+1) 
assert dfs(0, ch) == N+1	
	
line = sys.stdin.readline()
assert re.match(re2, line)
tbl = list(map(int, line.split()))	
assert len(tbl) == M	
for t in tbl:
	assert 1 <= t <= N	

line = sys.stdin.readline()
assert len(line) == 0
sys.exit(42)
