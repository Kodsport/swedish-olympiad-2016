#!/usr/bin/env python
import sys

data = []

for line in sys.stdin:
    if line.strip() != "":
        data.append(line.strip())

assert len(data) == 2

N = int(data[0])
assert 1 <= N <= 10

days = map(int, data[1].split())

assert all(0 <= day <= 30 for day in days)

sys.exit(42)
