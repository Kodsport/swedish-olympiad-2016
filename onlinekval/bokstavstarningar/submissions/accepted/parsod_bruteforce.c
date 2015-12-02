#include <stdio.h>

//Clever brute force, O( M*N*(N!) )

char tar[20][21];
char ord[100000][21];
int occurs[20][256];
int taken[20],t[20];
int tot;
int found[100000];
int N,K,M;

void MLX(int nr) {
  int i,j;
  if(nr==N) {
    for(i=0;i<M;i++) if(!found[i]) {
	for(j=0;j<N;j++) if(!occurs[t[j]][ord[i][j]]) break;
	if(j==N) {
	  tot++;
	  found[i]=1;
	}
      }
  }
  else {
    for(t[nr]=0;t[nr]<N;t[nr]++) if(!taken[t[nr]]) {
	taken[t[nr]]=1;
	MLX(nr+1);
	taken[t[nr]]=0;
      }
  }
}

int main() {
  char c;
  int i,j;
  scanf("%d %d %d", &N, &K, &M);
  
  for(i=0;i<N;i++) {
    for(c='A';c<='Z';c++) occurs[i][c]=0;
    scanf("%s", tar[i]);
    for(j=0;j<K;j++) occurs[i][tar[i][j]]=1;
    taken[i]=0;
  }
  for(i=0;i<M;i++) {
    scanf("%s", ord[i]);
    found[i]=0;
  }
  tot=0;
  MLX(0);
  printf("%d\n", tot);
  //for(i=0;i<N;i++) if(found[i]) printf("%s\n", ord[i]);
  return 0;
}
