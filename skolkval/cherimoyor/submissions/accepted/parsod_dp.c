#include <stdio.h>
#define NMAX 15
#define CMAX 30

// original by PS
// slightly edited by Arash
// modified by PS again adding memoization

int MIN(int p, int q) {return p<q?p:q; }
int MAX(int p, int q) {return p>q?p:q; }

int P[]={0,10,19,27,34,40,45,49,52,54,55};
int N;
int n[50];
int T[NMAX+2][CMAX+1][CMAX+1];

int MLX(int nr, int rem1, int rem2) {
        int p,q,eat0,eat1,eat2;
        p=0;
        if(nr==N+2) return 0;
	if(T[nr][rem1][rem2]!=-1) return T[nr][rem1][rem2];
        for(q=rem2;q<=MIN(10,rem1+rem2+n[nr]);q++) {
                eat2=MIN(q,rem2);
                eat1=MIN(q-eat2,rem1);
                eat0=MIN(q-eat1-eat2,n[nr]);
                p=MAX(p,P[q] + MLX(nr+1, n[nr]-eat0, rem1-eat1));
        }
	T[nr][rem1][rem2]=p;
        return p;
}

int main() {
        scanf("%d", &N);
        int i,j,k;
        for(i=0;i<N;i++) scanf("%d", &n[i]);
        n[N]=n[N+1]=0;
	for(i=0;i<N+2;i++) for(j=0;j<=CMAX;j++) for(k=0;k<=CMAX;k++) T[i][j][k]=-1;
        printf("%d\n", MLX(0,0,0));
        return 0;
}
