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
	vi k(N);
	vvi n(N, vi()), s(N, vi());
	rep(i, 0, N) {
		cin >> k[i];
		n[i].resize(k[i]);
		s[i].resize(k[i]);
		rep(j, 0, k[i]) {
			cin >> s[i][j] >> n[i][j];
			if(s[i][j] < 0) {
				s[i][j] *= -1;
				n[i][j] *= -1;
			}
		}
	}
	int ans = 0;
	rep(m, 0, 1 << 10) {
		int res = 0;
		rep(i, 0, N) {
			int sum = 0;
			rep(j, 0, k[i]) {
				int w = 1;
				if(m & (1 << (s[i][j]-1))) {
					w = -1;	
				}
				sum += w * n[i][j];
			}
			if(sum > 0) res += sum;
		}
		ans = max(ans, res);
	}
	cout << ans << endl;
	return 0;
}

