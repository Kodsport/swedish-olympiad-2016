import mafia
import sys

N, M = map(int, sys.stdin.readline().split())
A = [ int(t) for t in sys.stdin.readline().strip().split() ]
B = [ int(t) for t in sys.stdin.readline().strip().split() ]
T = [ int(t) for t in sys.stdin.readline().strip().split() ]
G = int(sys.stdin.readline())
C = [ int(t) for t in sys.stdin.readline().strip().split() ]

mafia.cops(N, M, A, B, T)
CS = map(str, map(mafia.guess, C))
print(' '.join(CS))
