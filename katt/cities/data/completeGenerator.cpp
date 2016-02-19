// Generates a test case with a complete binary tree of N nodes
// params: N K seed

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
	int K = atoi(argv[2]);
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

