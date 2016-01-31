// author: Emanuel Gedin
// expected score: 49

#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < int(b); i++)
#define trav(it, v) for(auto it = v.begin(); it != v.end(); it++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x).size()
 
bool canPay(int i, vector<int>& p, vector<bool> ok) {
	if (i == 0 || !ok[i]) return false;
	while (i != 0) {
		i = p[i];
		if (ok[i]) return false;
	}
	return true;
}

int main() {
	int N, M;
	cin >> N >> M;
	vector<int > p(N+1);
	rep(i, 1, N+1) {
		cin >> p[i];
	}
	vector<bool> ok(N+1, false);
	rep(i, 0, M) {
		int j;
		cin >> j;
		ok[j] = true;
	}
	int ans = 0;
	rep(i, 1, N) {
		if (canPay(i, p, ok)) ans++;
	}
	cout << ans << endl;
}

