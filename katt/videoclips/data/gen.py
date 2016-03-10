#!/usr/bin/env pypy

from __future__ import print_function
from __future__ import division
import subprocess
import random
import math
import sys

N = int(sys.argv[1])
M = int(sys.argv[2])
method = sys.argv[3]
random.seed(int(sys.argv[4]))

# Generates a few pretty wide trees, generally, with eventual cycles of
# rather small size. Good for testing correctness.
def gen_random(N):
    return [random.randint(0, N - 1) for _ in range(N)]

# Generate a single long path, as a possible worst case.
def gen_path(N):
    return [max(0, x) for x in range(N)]

# As above but in opposite direction.
def gen_path_reverse(N):
    return [min(N - 1, x+2) for x in range(N)]

# As above but in opposite direction.
def gen_no_cycle(N):
    return [random.randint(0, x) for x in range(N)]

# Generate a single cycle, with a small number of in-edges, as another worst case.
def gen_cycle(N):
    in_ed = N // 10
    cycle_ed = N - in_ed
    perm = list(range(cycle_ed))
    random.shuffle(perm)
    cycle = perm[:]
    for i in range(cycle_ed):
        cycle[perm[i]] = perm[(i+1) % cycle_ed]
    return cycle + [random.randint(0, cycle_ed) for _ in range(in_ed)]

lines = []
if method == 'random':
    lines += gen_random(N)
elif method == 'path':
    lines += gen_path(N)
elif method == 'reverse':
    lines += gen_path_reverse(N)
elif method == 'cycle':
    lines += gen_cycle(N)
elif method == 'nocycle':
    lines += gen_no_cycle(N)
else:
    assert False
lines = map(str, lines)


print("{} {}".format(N, M - random.randint(0, 100)))
print(' '.join(lines))
print(N)
print(' '.join(str(x) for x in range(N)))
