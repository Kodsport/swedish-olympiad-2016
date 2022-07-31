#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

vector<int> v[101010];
int c[101010][15];

ll u;

void dfs(int s, int e, int k) {
    c[s][0] = 1;
    for (int i = 0; i < v[s].size(); i++) {
        if (v[s][i] == e) continue;
        dfs(v[s][i],s,k);
        for (int j = 0; j < k; j++) {
            u += (ll)c[s][k-j-1]*c[v[s][i]][j];
        }
        for (int j = 0; j < k; j++) {
            c[s][j+1] += c[v[s][i]][j];
        }
    }
}

ll paths(int N, int K, int* F, int* T) {
    for (int i = 0; i < N-1; i++) {
        v[F[i]].push_back(T[i]);
        v[T[i]].push_back(F[i]);
    }
    dfs(0,-1,K);
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
