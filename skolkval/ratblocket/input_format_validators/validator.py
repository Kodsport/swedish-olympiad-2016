#!/usr/bin/python3
import sys

data = []

for line in sys.stdin:
    if line.strip() != "":
        data.append(line.strip())

assert len(data) > 0

line1 = data[0].split()
assert len(line1) == 2

N,M = list(map(int, line1))
assert 1 <= N <= 7
assert 1 <= M <= 7

assert len(data) == N + 1

a = 0
b = 0

for line in data[1:]:
  assert len(line) == M
  for c in line:
    if c == "A":
      a += 1
    elif c == "B":
      b += 1
    else:
      assert c in ".#c01"

assert a == 1
assert b == 1

sys.exit(42)
