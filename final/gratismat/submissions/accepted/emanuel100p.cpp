// author: Emanuel Gedin
// expected score: 100

#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < int(b); i++)
#define trav(it, v) for(auto it = v.begin(); it != v.end(); it++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x).size()
 
int solve(int i, vector<vector<int> >& ch, vector<bool>& ok) {
	if (ok[i]) return 1;
	int ret = 0;
	trav(it, ch[i]) {
		ret += solve(*it, ch, ok);	
	}
	return ret;
} 

int main() {
	int N, M;
	cin >> N >> M;
	vector<vector<int> > ch(N+1);
	rep(i, 1, N+1) {
		int j;
		cin >> j;
		ch[j].push_back(i);
	}
	vector<bool> ok(N+1, false);
	rep(i, 0, M) {
		int j;
		cin >> j;
		ok[j] = true;
	}
	cout << solve(0, ch, ok) << endl;
}

