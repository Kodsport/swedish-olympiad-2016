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

pii operator+(pii a, pii b) {
	return {a.first + b.first, a.second + b.second};
}

typedef vector<pii> vpii;
void add(vpii& dp, int nu, pii val) {
	for (int i = sz(dp); i --> nu;)
		dp[i] = max(dp[i], dp[i-nu] + val);
}

int main() {
	cin.sync_with_stdio(false);
	int N, M, K, B;
	cin >> N >> M >> K >> B;
	vector<vi> cats(M);
	rep(i,0,N) {
		int pnt, cat;
		cin >> pnt >> cat;
		cats[cat-1].push_back(pnt);
	}
	vpii dp(K+1);
	multiset<int> pq;
	trav(cat, cats) {
		pq.insert(sz(cat));
		vpii dp2 = dp;
		int sum = 0;
		trav(x, cat) {
			add(dp, 1, pii(x, 0));
			sum += x;
		}
		add(dp2, sz(cat), pii(sum + B, 1));
		rep(i,0,K+1) dp[i] = max(dp[i], dp2[i]);
	}
	int greedy = 0, avail = K;
	trav(x, pq) {
		avail -= x;
		if (avail < 0) break;
		greedy++;
	}
	cout << dp[K].first << endl;
	cerr << dp[K].second << '/' << greedy << endl;
}
