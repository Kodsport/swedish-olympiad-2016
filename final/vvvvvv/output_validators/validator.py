import sys
import re

indata = open(sys.argv[1], 'r')
s = indata.readline()
W=int(s.split()[0])
H=int(s.split()[1])
map=[[0 for y in range(H+1)] for x in range(W+1)]
for line in indata.readlines():
    [x1,y1,x2,y2]=[int(x) for x in line.split()]
    if(y1>y2): y1,y2=y2,y1
    if(x1>x2): x1,x2=x2,x1
    if(x1==x2):
      for y in range(y1,y2):
	map[x1][y]|=1
        if(x1>0): map[x1-1][y]|=2
    elif(y1==y2):
      for x in range(x1,x2):
	map[x][y1]|=4
        if(y1>0): map[x][y1-1]|=8


f = open(sys.argv[2], 'r')
judge_answer = f.readline().strip()
try:
  answer = sys.stdin.readline().strip()
  if not re.match("^[VHG]*$", answer):
    exit(43)
  if len(answer)>5000:
    exit(43)
  if W%2==0 and len(answer)!=len(judge_answer):    #Demand shortest solution if W is odd
    exit(43)
  x=y=anti=0
  for d in answer:
    if d=='V':
      if(x>0 and (map[x][y]&1)==0):
        x-=1
      else:
	exit(43)  #Goes out or into wall
    elif d=='H':
      if(x<W-1 and (map[x][y]&2)==0):
        x+=1
      else:
	exit(43)  #Goes out or into wall
    elif d=='G':
      anti=1-anti
    while(y>=0 and y<H and ((map[x][y]>>(2+anti)) & 1)==0): y = y+1 if anti else y-1
    if(y<0 or y>=H):
      exit(43)  #Falling out
  if x!=W-1 or y!=H-1: 
    exit(43)   #Wrong end position
except Exception:
  exit(43)

exit(42)
