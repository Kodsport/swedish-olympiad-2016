import tshirts
import sys

N = int(sys.stdin.readline())
L = [ int(t) for t in sys.stdin.readline().strip().split() ]
H = [ int(t) for t in sys.stdin.readline().strip().split() ]
T = [ int(t) for t in sys.stdin.readline().strip().split() ]

print(tshirts.tshirt(N, L, H, T))
