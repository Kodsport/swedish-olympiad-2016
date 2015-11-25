#include <stdio.h>

int todec(int R, int v[], int b[]) {
  int i,d,k;
  d=0;
  k=1;
  for(i=0;i<R;i++) {
    d+=k*v[i];
    k*=b[i];
  }
  return d;
}

void tokul(int R, int d, int v[], int b[]) {
  int i;
  for(i=0;i<R;i++) {
    v[i]=d%b[i];
    d/=b[i];
  }
}

int main() {
  int v[20],h[20],b[20];
  int i,j,k,N,M,R;
  scanf("%d",&R);
  for(i=R-1;i>=0;i--) {
    scanf("%d %d",&v[i],&h[i]);
    b[i]=v[i]+h[i]+1;
  }
  scanf("%d",&N); 
  M=todec(R,v,b);
  tokul(R,M+N,v,b);
  for(i=R-1;i>=0;i--) {
    printf("%d %d\n",v[i],b[i]-v[i]-1);
  }  
  return 0;
}
