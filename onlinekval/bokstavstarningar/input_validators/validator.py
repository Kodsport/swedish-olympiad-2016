#!/usr/bin/python3
import re
import sys

int_regex = "(0|[1-9][0-9]*)"

line = sys.stdin.readline()
assert re.match(int_regex + ' ' + int_regex + ' ' + int_regex + '$', line)
vals = [int(x) for x in line.split()]
assert len(vals) == 3
n = vals[0]
k = vals[1]
m = vals[2]
assert 1 <= n <= 15
assert 2 <= k <= 20
assert 1 <= m <= 10 ** 5

die_regex = '[A-Z]{' + str(k) + '}$'
word_regex = '[A-Z]{' + str(n) + '}$'
for i in range(0, n):
    line = sys.stdin.readline()
    assert re.match(die_regex, line)
    assert len(set(line)) == len(line)
wl = set()
for i in range(0, m):
    line = sys.stdin.readline()
    assert re.match(word_regex, line)
    wl.add(line.strip())

line = sys.stdin.readline()
assert len(line) == 0

assert len(wl) == m

sys.exit(42)
