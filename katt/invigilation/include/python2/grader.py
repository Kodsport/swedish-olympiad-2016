import invigilation
import sys

n, h = map(int, sys.stdin.readline().split())
xs, ys, zs = [], [], []
for i in range(n):
    x, y, z = map(int, sys.stdin.readline().split())
    xs.append(x)
    ys.append(y)
    zs.append(z)

print(invigilation.invigilation(n, h, xs, ys, zs))
