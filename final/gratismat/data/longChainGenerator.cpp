// Generates a long chain with many leaves at the end. All leaves are at the table.
// params: N seed

#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < int(b); i++)
#define trav(it, v) for(auto it = v.begin(); it != v.end(); it++)
#define all(x) x.begin(), x.end()

int main(int argc, char* argv[]) {
	if (argc < 3) {
		cerr << "Error: not enough arguments";
		return 0;
	}
	int N = atoi(argv[1]);
	int M = N/2;
	int seed = atoi(argv[2]);
	srand(seed);

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

