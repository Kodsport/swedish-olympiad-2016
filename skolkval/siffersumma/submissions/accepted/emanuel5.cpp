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
	string s;
	cin >> s;
	int l = s.size();
	vi N(l+1);
	vi ans(l+1);
	rep(i, 0, l) {
		N[i] = s[l-i-1] - '0';
	}
	int p = 0;
	int sum = 0;
	while(sum == 0 || N[p] == 9) {
		sum += N[p];
		p++;
	}
	sum--;
	rep(i, 0, p) {
		ans[i] = min(sum, 9);
		sum -= ans[i];
	}
	ans[p] = N[p] + 1;
	rep(i, p+1, l) {
		ans[i] = N[i];
	}
	if(ans[l] != 0) cout << ans[l];
	rep(i, 0, l) {
		cout << ans[l-i-1];
	}
	cout << endl;
}

