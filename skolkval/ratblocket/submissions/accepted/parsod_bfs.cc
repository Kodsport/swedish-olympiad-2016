#include <stdio.h>
int MIN(int p, int q) { return p<q?p:q;}

int INF=1000;
char map[10][11];
int N,M;

int invalid(int r, int c, int stat) {
  if(r<0 || r>=N || c<0 || c>=M) return 1;
  if (map[r][c]=='#') return 1;
  if ((map[r][c]=='0' || map[r][c]=='1') && (map[r][c]-'0' != stat)) return 1;
  return 0;
}

int encode(int r, int c, int ori, int stat) {
  return stat*300+ori*100+r*10+c;
}


void decode(int pos, int *r, int *c, int *ori, int *stat) {
  *c=pos%10;
  *r=(pos/10)%10;
  *ori=(pos/100)%3;
  *stat=pos/300;
}

int main() {
  int i,j,sr,sc,gr,gc,ori,stat,r,c,nori,nstat,nr,nc,now,next,m,dir,del,pos;
  int q[600], dist[600];
  scanf("%d %d", &N,&M);
  for(i=0;i<N;i++) scanf("%s", map[i]);
  for(i=0;i<N;i++) for(j=0;j<M;j++) {
      if(map[i][j]=='A') {
	sr=i;
	sc=j;
	map[i][j]='.';
      }
      if(map[i][j]=='B') {
	gr=i;
	gc=j;
	map[i][j]='.';
      }
      for(ori=0;ori<3;ori++) for(stat=0;stat<2;stat++) dist[encode(i,j,ori,stat)]=INF;
    }
  stat=0;
  r=sr;
  c=sc;
  ori=2;   //0=horizontal 1=vertical, 2=standing
  q[0]=encode(r,c,ori,stat);
  dist[q[0]]=0;
  now=0;
  next=1;
  while(now<next) {
    decode(q[now],&r,&c,&ori,&stat);
    for(m=0;m<4;m++) {
      dir=m/2;
      nc=c;
      nr=r;
      if(ori==2) {
	nori=dir;
	del=3*(m%2)-2;  // +1 or -2
      }
      else if(ori==dir) {
	nori=2;
	del=3*(m%2)-1;  // +2 or -1
      }
      else {
	nori=ori;
	del=2*(m%2)-1;  // +1 or -1
      }
      if(dir==0) nc=c+del;
      else nr=r+del;
      if(invalid(nr,nc,stat)) continue;
      if(nori==0 && invalid(nr,nc+1,stat)) continue;
      if(nori==1 && invalid(nr+1,nc,stat)) continue;
      nstat=(nori==2 && map[nr][nc]=='c')?(stat^1):stat;
      pos=encode(nr,nc,nori,nstat);
      if(dist[pos]==INF) {
	dist[pos]=dist[q[now]]+1;
	q[next++]=pos;
      }
    }
    now++;
  }
  printf("%d\n", MIN(dist[encode(gr,gc,2,0)],dist[encode(gr,gc,2,1)]));
  return 0;
}
