#include <stdio.h>
// original by PS

int MIN(int p, int q) {return p<q?p:q; }
int MAX(int p, int q) {return p>q?p:q; }

int P[]={0,10,19,27,34,40,45,49,52,54,55};
int n[10];

int MLX(int nr, int rem1, int rem2) {
        int p,q,eat0,eat1,eat2;
        p=0;
        if(nr==9) return 0;
        for(q=eat2;q<=MIN(10,rem1+rem2+n[nr]);q++) {
                eat2=MIN(q,rem2);
                eat1=MIN(q-eat2,rem1);
                eat0=MIN(q-eat1-eat2,n[nr]);
                p=MAX(p,P[q] + MLX(nr+1, n[nr]-eat0, rem1-eat1));
        }
        return p;
}

int main() {
        int i;
        for(i=0;i<7;i++) scanf("%d", &n[i]);
        n[7]=n[8]=0;
        printf("%d\n", MLX(0,0,0));
        return 0;
}
