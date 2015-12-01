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
	int N, K, M;
	cin >> N >> K >> M;
	vector<string> dice(N);
	vector<int> masks(N);
	rep(i,0,N) {
		cin >> dice[i];
		int m = 0;
		rep(j,0,K) m |= 1 << (dice[i][j] - 'A');
		masks[i] = m;
	}
	string word;
	int res = 0;
	rep(i,0,M) {
		cin >> word;
		vi reachable(1 << N), reachable2;
		reachable[0] = 1;
		rep(j,0,N) {
			reachable2.assign(1 << N, 0);
			int c = word[j] - 'A';
			rep(k,0,N) {
				if (!(masks[k] & 1 << c)) continue;
				rep(m,0,(1 << N)) {
					if (m & (1 << k)) continue;
					if (reachable[m]) reachable2[m | 1 << k] = 1;
				}
			}
			reachable.swap(reachable2);
		}
		if (reachable[(1 << N) - 1])
			res++;
	}
	cout << res << endl;
}
