import sys
import random

filename = sys.argv[1]

text = open(filename, "r").read().strip()

angles = []

def ang(num):
    lo = num * 22.5
    hi = (num + 1) * 22.5
    return random.uniform(lo + 1e-3, hi - 1e-3)

for x in text:
    asc = ord(x)
    a = asc//16
    b = asc%16
    angles.append(ang(a))
    angles.append(ang(b))

print("%d" % len(angles))
print('\n'.join(str(x) for x in angles))
