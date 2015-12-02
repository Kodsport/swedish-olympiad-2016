import re
import sys

if len(sys.argv) > 1:
    assert len(sys.argv) == 4
    n_max = int(sys.argv[1])
    k_max = int(sys.argv[2])
    xy_max = int(sys.argv[3])
else:
    n_max = 1000000
    k_max = 10 ** 18
    xy_max = 10 ** 18

int_regex = "(0|[1-9][0-9]*)"
intspace_regex = int_regex + "( " + int_regex + ")*"
line_regex = "^" + intspace_regex + " " + intspace_regex + "$"

line = sys.stdin.readline()
assert re.match(line_regex, line)
vals = [int(x) for x in line.split()]
assert len(vals) == 2
n = vals[0]
assert 1 <= n <= n_max

k = vals[1]
assert 1 <= k <= k_max

seen = set()

for i in range(0, n):
    s = sys.stdin.readline()
    assert re.match(line_regex, s)
    xy = [int(x) for x in s.split()]
    assert len(vals) == 2
    x = xy[0]
    y = xy[1]
    assert 0 <= x <= xy_max
    assert 0 <= y <= xy_max
    assert (x, y) not in seen
    assert (x, y - 1) not in seen
    assert (x, y + 1) not in seen
    seen.add((x, y))

line = sys.stdin.readline()
assert len(line) == 0

sys.exit(42)
