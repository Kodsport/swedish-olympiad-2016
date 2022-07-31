#include <iostream>

using namespace std;

typedef long long ll;

int x[101][101];

ll paths(int N, int K, int* F, int* T) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            x[i][j] = 1e9;
        }
    }
    for (int i = 0; i < N-1; i++) {
        x[F[i]][T[i]] = 1;
        x[T[i]][F[i]] = 1;
    }
    for (int c = 0; c < N; c++) {
        for (int a = 0; a < N; a++) {
            for (int b = 0; b < N; b++) {
                x[a][b] = min(x[a][b],x[a][c]+x[c][b]);
            }
        }
    }
    int u = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++) {
            if (x[i][j] == K) u++;
        }
    }
    return u;
}

int main() {
    int N, K;
	scanf("%d%d", &N, &K);
    int F[N - 1], T[N - 1];
    for (int i = 0; i < N-1; i++) scanf("%d", F + i);
    for (int i = 0; i < N-1; i++) scanf("%d", T + i);
	printf("%lld\n", paths(N,K,F,T));
}
