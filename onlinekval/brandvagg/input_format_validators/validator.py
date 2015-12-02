import re
import sys

int_regex = "(0|[1-9][0-9]*)$"

def int_range(x, lo, hi):
    assert re.match(int_regex, x)
    x = int(x)
    return (lo <= x <= hi)

def is_ip(v):
    pa = v.split('.')
    return len(pa) == 4 and all(int_range(x, 0, 255) for x in pa)

line = sys.stdin.readline()
assert re.match(int_regex, line)
nrules = int(line)
assert 1 <= nrules <= 100

for it in range(nrules):
    line = sys.stdin.readline().rstrip('\n')
    parts = line.split(' ')
    verb = parts[0]
    assert verb in ['accept', 'drop', 'log']
    cond = parts[1:]
    for c in cond:
        eq = c.split('=')
        assert len(eq) == 2
        (t,v) = eq
        if t == 'ip':
            assert is_ip(v)
        elif t == 'port':
            assert int_range(v, 0, 65535)
        elif t == 'limit':
            assert int_range(v, 1, 1000)
        else:
            assert False

line = sys.stdin.readline()
assert re.match(int_regex, line)
nreqs = int(line)
assert 1 <= nreqs <= 100

for it in range(nreqs):
    line = sys.stdin.readline().rstrip('\n')
    eq = line.split(':')
    assert len(eq) == 2
    assert int_range(eq[1], 0, 65535)
    assert is_ip(eq[0])

line = sys.stdin.readline()
assert len(line) == 0

sys.exit(42)
