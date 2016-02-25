#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

vector<int> v[101010];
int r[101010];

ll u;

int cc;
int z[101010];

void dfs1(int s, int e) {
    z[s] = 1;
    cc++;
    for (int i = 0; i < v[s].size(); i++) {
        if (v[s][i] == e || r[v[s][i]]) continue;
        dfs1(v[s][i],s);
        z[s] += z[v[s][i]];
    }
}

int find_center(int s) {
    cc = 0;
    dfs1(s,-1);
    if (cc == 1) return s;
    int x = s, e = -1;
    while (true) {
        int ux = -1;
        for (int i = 0; i < v[x].size(); i++) {
            if (v[x][i] == e || r[v[x][i]]) continue;
            if (ux == -1 || z[v[x][i]] > z[ux]) ux = v[x][i];
        }
        if (ux == -1 || z[ux] <= cc/2) break;
        e = x;
        x = ux;
    }
    return x;
}

int q[101010];

void dfs2(int s, int e, int c, int k) {
    if (c > k) return;
    u += q[k-c];
    for (int i = 0; i < v[s].size(); i++) {
        if (v[s][i] == e || r[v[s][i]]) continue;
        dfs2(v[s][i],s,c+1,k);
    }
}

void dfs3(int s, int e, int c, int k) {
    if (c > k) return;
    q[c]++;
    for (int i = 0; i < v[s].size(); i++) {
        if (v[s][i] == e || r[v[s][i]]) continue;
        dfs3(v[s][i],s,c+1,k);
    }
}

void search(int s, int k) {
    q[0] = 1;
    for (int i = 0; i < v[s].size(); i++) {
        if (r[v[s][i]]) continue;
        dfs2(v[s][i],s,1,k);
        dfs3(v[s][i],s,1,k);
    }
    for (int i = 0; i <= cc; i++) q[i] = 0;
}

ll paths(int N, int K, int* F, int* T) {
    for (int i = 0; i < N-1; i++) {
        v[F[i]].push_back(T[i]);
        v[T[i]].push_back(F[i]);
    }
    for (int i = 0; i < N; i++) {
        if (r[i]) continue;
        int x = find_center(i);
        if (cc == 1) continue;
        search(x,K);
        r[x] = 1;
        i--;
    }
    return u;
}

int main() {
    int N, K;
    cin >> N >> K;
    int F[N], T[N];
    for (int i = 0; i < N-1; i++) cin >> F[i];
    for (int i = 0; i < N-1; i++) cin >> T[i];
    cout << paths(N,K,F,T) << "\n";
}
