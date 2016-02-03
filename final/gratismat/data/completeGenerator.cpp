// Generates a test case with a complete tree of N nodes and M random people at the table.
// params: N M seed

#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < int(b); i++)
#define trav(it, v) for(auto it = v.begin(); it != v.end(); it++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x).size()

int main(int argc, char* argv[]) {
	if (argc < 4) {
		cerr << "Error: not enough arguments";
		return 0;
	}
	int N = atoi(argv[1]);
	int M = atoi(argv[2]);
	int seed = atoi(argv[3]);
	srand(seed);

	vector<int> par(N+1, 0);
	vector<int> a(N);
	rep(i, 0, N) {
		a[i] = i+1;
	}
	random_shuffle(a.begin(), a.end());
	rep(i, 1, N) {
		par[a[i]] = a[(i-1)/2];
	}

	vector<int> atTable(N);
	rep(i, 0, N) {
		atTable[i] = i+1;
	}
	random_shuffle(atTable.begin(), atTable.end());

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

