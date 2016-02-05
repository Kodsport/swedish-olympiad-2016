#include <stdio.h>

char DRAG[] = "VHS";

//Map: bitmask: 1 vanster 2 hoger 4 ner 8 upp

int dr[1000000],W,H;
int map[101][101], taken[100][100][2];

int MLX(int nr, int x, int y, int anti) {
  int newx, newy, newanti,i;
  if(taken[x][y][anti]) return 0;
  taken[x][y][anti]=1;
  if(x==W-1 && y==H-1) {
    for(i=0;i<nr;i++) printf("%c",DRAG[dr[i]]);
    printf("\n");
    return 1;
  }
  for(dr[nr]=0;dr[nr]<3;dr[nr]++) {
    newanti=anti;
    newx=x;
    if(dr[nr]==0) {
      if(x>0 && (map[x][y]&1)==0) newx--;
      else continue;
    }
    else if(dr[nr]==1) {
      if(x<W-1 && (map[x][y]&2)==0) newx++;
      else continue;
    }
    else {
      newanti=1-anti;
    }
    newy=y;
    while(newy>=0 && newy<H && ((map[newx][newy]>>(2+newanti)) & 1)==0) newy=(newanti?newy+1:newy-1);
    if(newy>=0 && newy<H && MLX(nr+1,newx,newy,newanti)) return 1;
  }
  return 0;
}

int main() {
  int x,y,N,x1,x2,y1,y2,i;
  scanf("%d %d %d", &W, &H, &N);
  for(x=0;x<W;x++) for(y=0;y<H;y++) map[x][y]=taken[x][y][0]=taken[x][y][1]=0;
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
  if(!MLX(0,0,0,0)) printf("Inte\n");
  return 0;
}
