import re
import sys

int_line_regex = "^(0|[1-9][0-9]*)$"
string_line_regex = "^[a-z]+$"

name = sys.stdin.readline()
assert re.match(string_line_regex, name)
assert 1 <= len(name) <= 10

s = set()
s.add(name)

line = sys.stdin.readline()
assert re.match(int_line_regex, line)
N = int(line)
assert 1 <= N <= 10000

for i in xrange(N-1):
    line = sys.stdin.readline()
    assert line not in s
    s.add(line)
    assert re.match(string_line_regex, line)
    assert 1 <= len(line) <= 21

line = sys.stdin.readline()
assert line == name

line = sys.stdin.readline()
assert len(line) == 0

sys.exit(42)
