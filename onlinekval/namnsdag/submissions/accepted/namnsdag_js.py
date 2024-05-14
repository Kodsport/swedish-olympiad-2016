#!/usr/bin/env python3
name = input()
n = int(input())
for i in range(n):
	inp = input()
	dif = sum(1 if x != y else 0 for x, y in zip(inp, name))
	if dif <= 1 and len(inp) == len(name):
		print((i+1))
		break
