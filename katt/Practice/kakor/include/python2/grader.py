import kakor
from sys import stdin

N = int(stdin.readline())
A = [int(x) for x in stdin.readline().split()]
print("%d" % kakor.cookies(N, A))
