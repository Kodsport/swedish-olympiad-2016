import re
import sys

int_regex = "(0|[1-9][0-9]*)"
intspace_regex = int_regex + "( " + int_regex + ")*"
line_regex = "^" + intspace_regex + " " + intspace_regex + "$"

line = sys.stdin.readline()
assert re.match(line_regex, line)
vals = [int(x) for x in line.split()]
assert len(vals) == 2
n = vals[0]
assert 1 <= n <= 1000000

k = vals[1]
assert 1 <= k <= 10 ** 18

seen = set()

for i in range(0, n):
    s = sys.stdin.readline()
    assert re.match(line_regex, s)
    xy = [int(x) for x in s.split()]
    assert len(vals) == 2
    x = xy[0]
    y = xy[1]
    assert 0 <= x <= 10 ** 18
    assert 0 <= y <= 10 ** 18
    assert (x, y) not in seen
    assert (x, y - 1) not in seen
    assert (x, y + 1) not in seen
    seen.add((x, y))

line = sys.stdin.readline()
assert len(line) == 0

sys.exit(42)
