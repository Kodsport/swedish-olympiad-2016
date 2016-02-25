// Generates a long chain with many leaves at the end. All leaves are at the table.
// params: N K seed

#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < int(b); i++)
#define trav(it, v) for(auto it = v.begin(); it != v.end(); it++)
#define all(x) x.begin(), x.end()

int main(int argc, char* argv[]) {
	if (argc < 4) {
		cerr << "Error: not enough arguments";
		return 0;
	}
	int N = atoi(argv[1]);
	int K = atoi(argv[2]);
	int seed = atoi(argv[3]);
	srand(seed);

	vector<int> nodes(N);
	rep(i, 0, N) {
		nodes[i] = i+1;
	}
	random_shuffle(nodes.begin(), nodes.end());

	vector<int> par(N+1);
	int p = 0;
	rep(i, 0, (N+1)/2) {
		int u = nodes[i];
		par[u] = p;
		p = u;
	}
	rep(i, (N+1)/2, N) {
		int u = nodes[i];
		par[u] = p;
	}

	cout << N << " " << K << endl;
	bool first = true;
	rep(i, 1, N+1) {
		if (par[i] == 0) continue;
		if (!first) cout << " ";
		first = false;
		cout << par[i]-1;
	}
	cout << endl;
	first = true;
	rep(i, 1, N+1) {
		if (par[i] == 0) continue;
		if (!first) cout << " ";
		first = false;
		cout << i-1;
	}
	cout << endl;
}
