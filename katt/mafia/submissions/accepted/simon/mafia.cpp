#include <bits/stdc++.h>
#include "mafia.h"
using namespace std;

#define rep(i, from, to) for (int i = from; i < (to); ++i)
#define trav(a, x) for (auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
void PR(vi &v) { trav(x, v) cout << x << ' '; cout << endl; }

vector<ll> results;

const ll inf = 1000000000000000001LL;

void cops(int N, int M, int A[], int B[], int T[]) {
	vector<vector<pii>> ed(N);
	rep(i,0,M) {
		ed[A[i]].emplace_back(B[i], T[i]);
		ed[B[i]].emplace_back(A[i], T[i]);
	}
	vi color(N);
	vector<ll> dp(N+1), dp2;
	dp[0] = 1;
	rep(i,0,N) {
		if (color[i]) continue;
		int white = 0, black = 0;
		vector<pii> q = {pii(i, 1)};
		while (!q.empty()) {
			pii pa = q.back();
			q.pop_back();
			int x = pa.first, c = pa.second;
			if (color[x]) continue;
			color[x] = c;
			if (c == 1) white++;
			else black++;
			trav(e, ed[pa.first]) {
				int y = e.first;
				int z = e.second;
				int c2 = (z == 2 ? 3 - c : c);
				q.emplace_back(y, c2);
			}
		}
		dp2.assign(N+1, 0);
		rep(j,0,N+1) {
			if (j + white <= N) dp2[j + white] += dp[j];
			if (j + black <= N) dp2[j + black] += dp[j];
			dp2[j] = min(dp2[j], inf);
		}
		dp.swap(dp2);
	}
	results = move(dp);
}

ll guess(int C) {
	assert(0 <= C && C < sz(results));
	assert(results[C] < inf);
	return results[C];
}
