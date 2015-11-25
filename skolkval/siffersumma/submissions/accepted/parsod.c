#include <stdio.h>
#include <string.h>
int MIN(int p, int q) {return p<q?p:q;}

int main() {
  int N[100],i,k,m,p,ss;
  char inp[101];	
  scanf("%s", inp);
  m=0;
  for(i=strlen(inp)-1;i>=0;i--) N[m++]=inp[i]-'0';
  N[m++]=0;
  //Find the digit to be increased.
  ss=N[0];
  for(k=1;k<m;k++) {  
    if(N[k]<9 && 0<=ss-1 && ss-1<=k*9) break; 
    ss+=N[k];
  }
  N[k]+=1; 
  ss--;
  //Fill up to the remaining digit sum.
  for(p=0;p<k;p++) {
    N[p]=MIN(ss,9);
    ss-=N[p];
  }
  for(p=m-1;p>=0;p--) if(p<m-1 || N[p]>0) printf("%d",N[p]);
  printf("\n");
  return 0;
}
