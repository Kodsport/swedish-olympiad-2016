#include <bits/stdc++.h>

using namespace std;

int dfs(int at, const vector<bool>& eating, const vector<vector<int>>& children) {
	if(eating[at]) return 1;
	int ans = 0;
	for(int i : children[at]) ans += dfs(i, eating, children);
	return ans;
}

int main() {
	int N, M;
	cin >> N >> M;
	vector<vector<int>> children(N + 1);
	for(int i = 1; i <= N; ++i){
		int p;
		cin >> p;
		children[p].push_back(i);
	}
	vector<bool> eating(N + 1);
	for(int i = 1; i <= N; ++i){
		int p;
		cin >> p;
		eating[p] = true;
	}
	cout << dfs(0, eating, children) << endl;
}
