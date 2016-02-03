// Generates a long chain with many leaves at the end. All leaves are at the table.
// params: N

#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < int(b); i++)
#define trav(it, v) for(auto it = v.begin(); it != v.end(); it++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x).size()

void treeDfs(int i, vector<vector<int> >& adj, vector<int>& par) {
	trav(it, adj[i]) {
		if (*it != par[i]) {
			par[*it] = i;
			treeDfs(*it, adj, par);
		}
	}
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		cerr << "Error: not enough arguments";
		return 0;
	}
	srand(time(NULL));
	int N = atoi(argv[1]);
	int M = N/2;

	vector<int> nodes(N);
	rep(i, 0, N) {
		nodes[i] = i+1;
	}
	random_shuffle(nodes.begin(), nodes.end());

	vector<int> par(N+1);
	vector<int> atTable(M);
	int p = 0;
	rep(i, 0, (N+1)/2) {
		int u = nodes[i];
		par[u] = p;
		p = u;
	}
	rep(i, (N+1)/2, N) {
		int u = nodes[i];
		par[u] = p;
		atTable[i - (N+1)/2] = u;
	}

	cout << N << " " << M << endl;
	rep(i, 1, N+1) {
		cout << par[i];
		if (i == N) cout << endl;
		else cout << " ";
	}
	rep(i, 0, M) {
		cout << atTable[i];
		if (i == M - 1) cout << endl;
		else cout << " ";

	}
}

