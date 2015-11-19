import sys
import re

indata = open(sys.argv[1], 'r')
n = int(indata.readline())
s = indata.readline()
f = open(sys.argv[2], 'r')
judge_answer = f.readline().strip()
try:
  answer = sys.stdin.readline().strip()
  if not re.match("^[RGB]*$", s):
      exit(43)
  if len(answer)!=n:
      exit(43)
  now=0
  for c in answer: now=s.find(c,now)+1
  jnow=0
  for c in judge_answer: jnow=s.find(c,jnow)+1
  if now != jnow:
      exit(43)
except Exception:
  exit(43)

exit(42)
