import re
import sys

int_regex = "(0|[1-9][0-9]*)"
intspace_regex = int_regex + "( " + int_regex+")*"
line_regex = "^" + intspace_regex + "$"

line = sys.stdin.readline()
assert re.match(line_regex, line)
vals=[int(x) for x in line.split()]
assert len(vals)==1
n=vals[0]
assert 1 <= n <= 25
s = sys.stdin.readline()
assert re.match("^[RGB]*$", s)
assert 3 <= len(s) <= 200
line = sys.stdin.readline()
assert len(line) == 0

#Check that robot stays inside string
now=0
for i in range(n):
   m=-1
   for c in ('R','G','B'):
	k=s.find(c,now)
	assert k>=0
	m=max(m,k)
   now=m+1
sys.exit(42)
