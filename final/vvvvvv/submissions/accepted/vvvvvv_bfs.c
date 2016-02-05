#include <stdio.h>

char DRAG[] = "VHG";

//Map: bitmask: 1 vanster 2 hoger 4 ner 8 upp


int main() {
  int x,y,N,x1,x2,y1,y2,i,j,d,anti;
  int newx, newy, newanti,now,next,newpos;
  int W,H;
  int map[101][101], p[20000],q[20000];
  int best;
  char dr[20000],bra[20001];
  scanf("%d %d %d", &W, &H, &N);
  for(x=0;x<W;x++) for(y=0;y<H;y++) map[x][y]=0;
  for(i=0;i<N;i++) {
    scanf("%d %d %d %d", &x1,&y1,&x2,&y2);
    if(y1>y2) {y=y1; y1=y2; y2=y; }
    if(x1>x2) {x=x1; x1=x2; x2=x; }
    if(x1==x2) {
      for(y=y1;y<y2;y++) {
	map[x1][y]|=1;
	if(x1>0) map[x1-1][y]|=2;
      }
    }
    else if(y1==y2){
      for(x=x1;x<x2;x++) {
	map[x][y1]|=4;
	if(y1>0) map[x][y1-1]|=8;
      }
    }
    else {
      printf("Error\n");
      return 1;
    }
  }
  for(x=0;x<W;x++) for(y=0;y<H;y++) for(i=0;i<2;i++) p[i*H*W+x*H+y]=-1;
  now=0;
  q[0]=0; //State = anti*H*W + x*H + y
  p[0]=-2; //we don't want to find it again
  next=1;
  while(now<next) {
    anti=q[now]/(H*W);
    x=(q[now]%(H*W))/H;
    y=q[now]%H;
    if(x==W-1 && y==H-1) break;
    for(d=0;d<3;d++) {
      newanti=anti;
      newx=x;
      if(d==0) {
	if(x>0 && (map[x][y]&1)==0) newx--;
	else continue;
      }
      else if(d==1) {
	if(x<W-1 && (map[x][y]&2)==0) newx++;
	else continue;
      }
      else {
	newanti=1-anti;
      }
      newy=y;
      while(newy>=0 && newy<H && ((map[newx][newy]>>(2+newanti)) & 1)==0) newy=(newanti?newy+1:newy-1);
      if(newy>=0 && newy<H) {
	newpos=newanti*H*W + newx*H + newy;
	if(p[newpos]==-1) {
	  p[newpos]=q[now];
	  dr[newpos]=DRAG[d];
	  q[next++]=newpos;

	}
      }
    }
    now++;
  }
  if(x==W-1 && y==H-1) {
    for(i=q[now],j=0;i>0;i=p[i]) bra[j++]=dr[i];
    for(j--;j>=0;j--) printf("%c",bra[j]);
    printf("\n");
  }
  else printf("Inte\n");

  return 0;
}
