import regskylt
from sys import stdin

N = int(stdin.readline().split())
for i in range(N):
    t = [int(x) for x in stdin.readline().split()]
    print(regskylt.plate(t))
