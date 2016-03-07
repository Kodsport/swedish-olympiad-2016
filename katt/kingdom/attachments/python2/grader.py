import grader
import kingdom
import sys

_parts = []

def parts(R):
  global _parts
  _parts = R


def _grader_init():
  N, P = map(int, sys.stdin.readline().split())
  C = [ int(t) for t in sys.stdin.readline().strip().split() ]
  F = [ int(t) for t in sys.stdin.readline().strip().split() ]
  T = [ int(t) for t in sys.stdin.readline().strip().split() ]

  print(kingdom.division(N, P, C, F, T))
  print(' '.join([str(x) for x in _parts]))

if __name__ != "__main__":                                                          
  grader._grader_init()
