#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < int(to); ++i)
#define trav(a, x) for (auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
void PR(vi &v) { trav(x, v) cout << x << ' '; cout << endl; }

void add(vi& dp, int nu, int val) {
	for (int i = sz(dp); i --> nu;)
		dp[i] = max(dp[i], dp[i-nu] + val);
}

int main() {
	cin.sync_with_stdio(false);
	int N, M, K, B;
	cin >> N >> M >> K >> B;
	vector<vi> cats(M);
	int Pnt = -1;
	rep(i,0,N) {
		int pnt, cat;
		cin >> pnt >> cat;
		assert(0 < pnt && pnt <= 1000);
		if (Pnt == -1) Pnt = pnt;
		else assert(Pnt == pnt);
		cats[cat-1].push_back(pnt);
	}
	vi dp(K+1);
	trav(cat, cats) {
		vi dp2 = dp;
		int sum = 0;
		trav(x, cat) {
			add(dp, 1, x);
			sum += x;
		}
		add(dp2, sz(cat), sum + B);
		rep(i,0,K+1) dp[i] = max(dp[i], dp2[i]);
	}
	cout << dp[K] << endl;
}
