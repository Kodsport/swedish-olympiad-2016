import sys
import random

case = sys.argv[1]
length = int(sys.argv[2])
s = int(sys.argv[3])

random.seed(s)

def ang(num):
    global case
    lo = num * 22.5
    hi = (num + 1) * 22.5
    if case == "integers":
        return round(random.uniform(lo + 0.6, hi - 0.6))
    else:
        return random.uniform(lo + 1e-3, hi - 1e-3)

N = length // 2

print("%d" % (2*N))
for i in range(N):
    char = random.randint(32, 126)
    a = char // 16
    b = char % 16
    print(ang(a))
    print(ang(b))
