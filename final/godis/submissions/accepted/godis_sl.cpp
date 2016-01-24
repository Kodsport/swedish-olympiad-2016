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

int main() {
	cin.sync_with_stdio(false);
	int N;
	cin >> N;
	vector<vector<pii>> ths(N);
	rep(i,0,N) {
		int k;
		cin >> k;
		vector<pii>& th = ths[i];
		rep(j,0,k) {
			int s, n;
			cin >> s >> n;
			if (s < 0) {
				s = -s;
				n = -n;
			}
			th.emplace_back(s-1, n);
		}
	}
	int best = 0;
	rep(b,0,(1 << 10)) {
		int tot = 0;
		rep(i,0,N) {
			int su = 0;
			trav(pa, ths[i])
				su += pa.second * (b & 1 << pa.first ? 1 : -1);
			if (su > 0) tot += su;
		}
		best = max(best, tot);
	}
	cout << best << endl;
}
