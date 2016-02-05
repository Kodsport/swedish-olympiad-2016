#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < int(to); ++i)
#define trav(a, x) for (auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

ll solve(vi& v) {
	sort(all(v), greater<int>());
	ll res = 0, acc = 0;
	trav(x, v) {
		acc += x;
		res += acc;
	}
	return res;
}

int main() {
	cin.sync_with_stdio(false);
	int N, k = 0;
	cin >> N;
	int M = 0;
	ll res = 0, mid = 0;
	vi starts, ends;
	rep(i,0,N) {
		int m;
		cin >> m;
		M += m;
		vi a(m);
		rep(j,0,m) cin >> a[j];
		if (m == 0)
			;
		else if (m == 1) {
			res += a[0];
			mid += a[0];
		}
		else {
			rep(j,1,m-1)
				mid += a[j];
			starts.push_back(a.front());
			ends.push_back(a.back());
			k++;
		}
	}
	assert(M <= 10);
	res += k * mid;
	res += solve(starts);
	res += solve(ends);
	cout << res << endl;
}
