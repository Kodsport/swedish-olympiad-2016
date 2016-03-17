#/usr/bin/env python
import sys
import re

line = sys.stdin.readline()
assert re.match('^[0-9]+\n$', line)
N = int(line.strip())
assert 1 <= N <= 100000

line = sys.stdin.readline()
assert re.match('^[ab]+\n$', line)
line = line.strip()
assert len(line) == N

assert sys.stdin.read() == ''
sys.exit(42)
