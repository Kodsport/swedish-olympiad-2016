#!/usr/bin/env python3
import sys
import random

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))

needle = "UUNNVHVHBA"
alphabet = cmdlinearg("alphabet", "UNHVBA")
n = int(cmdlinearg("n"))
ar = [random.choice(alphabet) for _ in range(n)]
exc = sorted(random.sample(range(n), len(needle)))
for pos, ch in zip(exc, needle):
    ar[pos] = ch

print(''.join(ar))
