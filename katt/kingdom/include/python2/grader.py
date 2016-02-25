import cities
import sys

N, K = map(int, sys.stdin.readline().split())
F = [ int(t) for t in sys.stdin.readline().strip().split() ]
T = [ int(t) for t in sys.stdin.readline().strip().split() ]

print(cities.paths(N, K, F, T))
