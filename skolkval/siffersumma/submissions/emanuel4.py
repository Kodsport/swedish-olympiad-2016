#!/usr/bin/python3

import sys

def digitSum(N):
	return sum(map(int, str(N)))

N = int(sys.stdin.readline())
ans = N + 1
while digitSum(ans) != digitSum(N):
	ans += 1
print(ans)	
