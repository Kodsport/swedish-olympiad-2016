#include <algorithm>
#include <vector>
#include <iostream>
#include <map>
#include <queue>

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
	cin.exceptions(~cin.goodbit);
	int N;
	ll K;
	cin >> N >> K;
	map<ll, vector<pair<ll, int> > > xs;
	rep(i,0,N) {
		ll x, y;
		cin >> x >> y;
		xs[x].push_back({y, i});
	}
	vector<vector<pair<int, ll> > > ed(N);

	trav(pa, xs) {
		sort(all(pa.second));
	}
	trav(pa, xs) {
		trav(pa2, pa.second) {
			ll y = pa2.first;
			int i1 = pa2.second;
			for (int d = -1; d <= 1; d += 2) {
				ll x = pa.first+d;
				auto& oth = xs[x];
				auto afterit = lower_bound(all(oth), make_pair(y,N)), it = afterit;
				if (afterit != oth.begin()) {
					--it;
					int i2 = it->second;
					if (afterit != oth.end() && afterit->first == y+1) continue;
					ll dist = y - it->first;
					ed[i1].push_back({i2, dist});
					ed[i2].push_back({i1, dist});
				}
			}
		}
	}

	auto works = [&](ll k) {
		vector<bool> seen(N);
		queue<int> q;
		q.push(0);
		while (!q.empty()) {
			int x = q.front();
			q.pop();
			if (seen[x]) continue;
			seen[x] = true;
			trav(pa, ed[x]) {
				if (pa.second <= k)
					q.push(pa.first);
			}
		}
		return (bool)seen[N-1];
	};

	if (!works(K-1)) {
		cout << "NATT" << endl;
		return 0;
	}
	ll lo = -1, hi = K;
	while (lo + 1 < hi) {
		ll mid = (lo + hi) / 2;
		if (works(mid))
			hi = mid;
		else
			lo = mid;
	}
	cout << hi << endl;
}
