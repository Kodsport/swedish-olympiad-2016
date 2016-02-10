#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < int(to); ++i)
#define trav(a, x) for (auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int N;

int guess(const string& g) {
	int r;
	cout << g << endl;
	cin >> r;
	if (r == N) exit(0);
	return r;
}

int main() {
	cin.sync_with_stdio(false);
	cin >> N;
	string g(N, '0');
	int cor = guess(g);
	rep(i,0,N) {
		g[i] = '1';
		int cor2 = guess(g);
		if (cor2 < cor) g[i] = '0';
	}
	assert(false);
}
