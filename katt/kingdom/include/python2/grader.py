import grader
import kingdom
import sys

parts = []

def part(R):
	parts.add(R)

N, P = map(int, sys.stdin.readline().split())
C = [ int(t) for t in sys.stdin.readline().strip().split() ]
F = [ int(t) for t in sys.stdin.readline().strip().split() ]
T = [ int(t) for t in sys.stdin.readline().strip().split() ]

print(kingdom.division(N, K, F, T))
print(len(parts))
for part in parts:
	sys.stdout.write(str(len(part)))
	for i, e in enumerate(part):
		if i != 0:
			sys.stdout.write(" ")
		sys.stdout.write(str(e))
	sys.stdout.write("\n")
