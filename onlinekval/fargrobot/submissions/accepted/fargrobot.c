#include <stdio.h>

int MASK[256];

int main() {
  int N,i,k,m;
  char s[1001];
  MASK['R']=1;
  MASK['B']=2;
  MASK['G']=4;
  scanf("%d %s", &N, s);
  k=0;
  m=0;
  i=0;
  while(i<N) {
    m|=MASK[s[k]];
    if(m==7) {
      m=0; 
      printf("%c", s[k]);
      i+=1;
    }
    k++;
  }
  printf("\n");
  return 0;
}
