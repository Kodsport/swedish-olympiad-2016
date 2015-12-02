#!/usr/bin/env python2
name = raw_input()
n = int(raw_input())
for i in range(n):
        inp = raw_input()
	dif = sum(1 if x != y else 0 for x, y in zip(inp, name))
        dif += abs(len(name) - len(inp))
	if dif <= 1:
		print(i+1)
		break
