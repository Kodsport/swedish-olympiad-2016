#!/usr/bin/env python3
name = input()
n = int(input())
for i in range(n):
	dif = sum(1 if x != y else 0 for x, y in zip(input(), name))
	if dif <= 1:
		print(i+1)
		break
