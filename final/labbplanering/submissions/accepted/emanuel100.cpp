#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < int(b); i++)
#define trav(it, v) for(auto it = v.begin(); it != v.end(); it++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x).size()
 
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi; 
 
int main() {
	int N;
	cin >> N;
	ll ans = 0, middle = 0;
	vi s, e;
	rep(i, 0, N) {
		int m;
		cin >> m;
		if (m == 1) {
			int a;
			cin >> a;
			ans += a;
			middle += a;
		} else {
			int a;
			cin >> a;
			s.push_back(a);
			rep(j, 1, m-1) {
				cin >> a;
				middle += a;
			}
			cin >> a;
			e.push_back(a);
		}
	}
	ans += middle * (ll)sz(s);
	sort(all(s));
	sort(all(e));
	rep(i, 0, sz(s)) {
		ans += (ll)(i+1) * (ll)(s[i] + e[i]);
	}
	cout << ans << endl;
}

