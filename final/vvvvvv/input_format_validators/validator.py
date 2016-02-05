import re
import sys

int_regex = "(0|[1-9][0-9]*)"
intspace_regex = int_regex + "( " + int_regex+")*"
line_regex = "^" + intspace_regex + "$"

line = sys.stdin.readline()
assert re.match(line_regex, line)
vals=[int(x) for x in line.split()]
assert len(vals)==3
W=vals[0]
H=vals[1]
N=vals[2]
assert 1 <= n <= 5000
below = above = False
for i in range(n):
   s = sys.stdin.readline()
   assert re.match(line_regex, line)
   vals=[int(x) for x in line.split()]
   assert len(vals)==3
   x1,y1,x2,y2 = vals
   assert 0 <= x1 <= W
   assert 0 <= x2 <= W
   assert 0 <= y1 <= H
   assert 0 <= y2 <= H
   assert (x1==x2 and y1!=y2) or (y1==y2 and x1!=x2)
   if y1==0 and y2==0 and min(x1,x2)==0:
      below = True
   if y1==H and y2==H and max(x1,x2)==W:
      above = True
      
assert below and above
line = sys.stdin.readline()
assert len(line) == 0
sys.exit(42)
