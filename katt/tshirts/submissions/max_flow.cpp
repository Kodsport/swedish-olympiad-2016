#include <cstdio>
#include <cassert>
#include <tuple>
#include <vector>
#include <cstring>
#include <map>

using namespace std;

/*
 * This solution should solve test groups 1 and 3 and get 7+13 = 20 points (at
 * least).
 */

const int INF = 2147483647;

#define MAXV 3010
int q[MAXV], d[MAXV], p[MAXV];
struct flow_network {
    struct edge {
        int v, cap, nxt;
        edge(int _v, int _cap, int _nxt) : v(_v), cap(_cap), nxt(_nxt) {  }
    };
    int n, ecnt, *head;
    vector<edge> e, e_store;
    flow_network(int _n, int m = -1) : n(_n), ecnt(0) {
        e.reserve(2 * (m == -1 ? n : m));
        memset(head = new int[n], -1, n << 2);
    }
    void destroy() { delete[] head; }
    void reset() { e = e_store; }
    void add_edge(int u, int v, int uv, int vu=0) {
        e.push_back(edge(v, uv, head[u])); head[u] = ecnt++;
        e.push_back(edge(u, vu, head[v])); head[v] = ecnt++;
    }
    int max_flow(int s, int t, bool res = true) {
        if (s == t) return 0;
        e_store = e;
        int f = 0, l, r, v;
        while (true) {
            memset(d, -1, n << 2);
            memset(p, -1, n << 2);
            l = r = 0, d[q[r++] = s] = 0;
            while (l < r)
                for (int u = q[l++], i = head[u]; i != -1; i = e[i].nxt)
                    if (e[i].cap > 0 &&
                            (d[v = e[i].v] == -1 || d[u] + 1 < d[v]))
                        d[v] = d[u] + 1, p[q[r++] = v] = i;
            if (p[t] == -1) break;
            int x = INF, at = p[t];
            while (at != -1) x = min(x, e[at].cap), at = p[e[at^1].v];
            at = p[t], f += x;
            while (at != -1)
                e[at].cap -= x, e[at^1].cap += x, at = p[e[at^1].v];
        }
        if (res) reset();
        return f;
    }
};

int tshirt(int N, vector<int> L, vector<int> H, vector<int> T) {

    map<pair<int,int>, int> lid, lcnt;
    map<int, int> rid, rcnt;

    for (int i = 0; i < N; i++) {
        pair<int,int> cur(L[i], H[i]);
        if (lid.find(cur) == lid.end()) {
            lid.insert(make_pair(cur, lid.size()));
        }
        lcnt[cur]++;

        if (rid.find(T[i]) == rid.end()) {
            rid.insert(make_pair(T[i], rid.size()));
        }
        rcnt[T[i]]++;
    }

    int SOURCE = 0,
        SINK = 1,
        LEFT = 2,
        RIGHT = LEFT + lcnt.size(),
        CNT = RIGHT + rcnt.size();

    flow_network g(CNT);
    for (map<pair<int,int>, int>::const_iterator it = lid.begin(); it != lid.end(); ++it) {
        g.add_edge(SOURCE, LEFT + it->second, lcnt[it->first]);
        for (map<int, int>::const_iterator jt = rid.begin(); jt != rid.end(); ++jt) {
            if (it->first.first <= jt->first && jt->first <= it->first.second) {
                g.add_edge(LEFT + it->second, RIGHT + jt->second, INF);
            }
        }
    }
    for (map<int, int>::const_iterator it = rid.begin(); it != rid.end(); ++it) {
        g.add_edge(RIGHT + it->second, SINK, rcnt[it->first]);
    }

    return g.max_flow(SOURCE, SINK);
}

int main() {
    int N;
    ignore = scanf("%d", &N);
    vector<int> L(N), H(N), T(N);
    for (int i = 0; i < N; ++i) {
        ignore = scanf("%d", &L[i]);
    }
    for (int i = 0; i < N; ++i) {
        ignore = scanf("%d", &H[i]);
    }
    for (int i = 0; i < N; ++i) {
        ignore = scanf("%d", &T[i]);
    }
    printf("%d\n", tshirt(N, L, H, T));
}
