#include <stdio.h>
#include <string.h>

int MASK[256];

int main() {
  int N,M,i,j,k,m;
  char s[1001];
  int t[1001],mult[1001];
  MASK['R']=1;
  MASK['B']=2;
  MASK['G']=4;
  scanf("%d %s", &N, s);
  M=strlen(s);
  for(j=-1;j<M;j++) t[j+1]=-1;
  t[0]=0;
  mult[0]=1;
  for(i=0;i<N;i++) {
    for(j=-1;j<M;j++) if(t[j+1]==i) {
	//printf("%d %d %d\n", j+1, t[j+1], mult[j+1]);
	k=j+1;
	m=0;
	while(m!=7) {
	  if((m&MASK[s[k]])==0) {
	    //printf("Setting %d\n", k+1);
	    if(t[k+1]==-1) {
	      t[k+1]=t[j+1]+1;
	      mult[k+1]=mult[j+1];
	    }
	    else if (t[k+1]==t[j+1]+1) mult[k+1]+=mult[j+1];
	  }
	  m|=MASK[s[k]];
	  k++;
	}
      }
  }
  for(j=M-1;t[j+1]==-1;j--) {}
  printf("%d: %d (mult %d)\n", j+1, t[j+1],mult[j+1]);
  return 0;
}
