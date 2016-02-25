#include "cities.h"
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

vector<int> v[101010];

ll u;

void dfs(int s, int e, int c, int k) {
    if (c == k) {
        u++;
        return;
    }
    for (int i = 0; i < v[s].size(); i++) {
        if (v[s][i] == e) continue;
        dfs(v[s][i],s,c+1,k);
    }
}

ll paths(int N, int K, int* F, int* T) {
    for (int i = 0; i < N-1; i++) {
        v[F[i]].push_back(T[i]);
        v[T[i]].push_back(F[i]);
    }
    for (int i = 0; i < N; i++) dfs(i,-1,0,K);
    return u/2;
}
