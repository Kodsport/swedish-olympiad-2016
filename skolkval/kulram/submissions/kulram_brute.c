#include <stdio.h>

int main() {
  int v[20],h[20],b[20];
  int i,j,k,R;
  long long N;
  scanf("%d",&R);
  for(i=R-1;i>=0;i--) {
    scanf("%d %d",&v[i],&h[i]);
    b[i]=v[i]+h[i]+1;
  }
  scanf("%lld",&N); 
  for(;N>0;N--) {
    for(i=0;i<R;i++) if(h[i]>0) break;
    if(i<R) {
      h[i]--;
      v[i]++;
    }
    for(j=0;j<i;j++) {
      h[j]+=v[j];
      v[j]=0;
    }
  }
  for(i=R-1;i>=0;i--) {
    printf("%d %d\n",v[i],h[i]);
  }  
  return 0;
}
