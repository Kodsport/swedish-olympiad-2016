import sys
n=int(sys.stdin.readline())
s=sys.stdin.readline().strip()
now=0
for i in range(n):
   m=1000
   for c in ('R','G','B'):
        k=s.find(c,now)
        assert k>=0
        m=min(m,k)     #Oops, taking min instead of max
   sys.stdout.write(s[m])
   now=m+1
sys.stdout.write('\n')
