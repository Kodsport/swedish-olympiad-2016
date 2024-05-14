#!/usr/bin/python3
import videoclips
import sys

K, M = map(int, sys.stdin.readline().split())
S = [ int(t) for t in sys.stdin.readline().strip().split() ]
videoclips.videos(K, M, S)

N = int(sys.stdin.readline())
I = [ int(t) for t in sys.stdin.readline().strip().split() ]
IS = map(str, map(videoclips.clip, I))
print(' '.join(IS))
