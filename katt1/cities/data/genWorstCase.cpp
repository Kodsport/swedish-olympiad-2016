// Generates a long chain with two stars at the end.
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
	int seed = atoi(argv[2]);
	srand(seed);

	int K = N / 3 + 2;
	int midnodes = N / 3 + 1;
	int rnodes = N - midnodes;
	int leftnodes = rnodes / 2;
	int rightnodes = rnodes - rnodes / 2;

	cout << N << ' ' << K << endl;
	int n = 0;
	vector<int> L, R;
	rep(i,0,midnodes-1) {
		L.push_back(n);
		R.push_back(n+1);
		n++;
	}
	n++;
	int a = 0, b = midnodes-1;
	rep(i,0,leftnodes) {
		L.push_back(n++);
		R.push_back(a);
	}
	rep(i,0,rightnodes) {
		L.push_back(n++);
		R.push_back(b);
	}

	assert((int)L.size() == N-1);
	assert((int)R.size() == N-1);
	rep(i,0,N-1) {
		if (rand() & 16)
			swap(L[i], R[i]);
	}
	int r = rand();
	srand(r);
	random_shuffle(all(L));
	srand(r);
	random_shuffle(all(R));
	rep(i,0,N-1) {
		if (i) cout << ' ';
		cout << L[i];
	}
	cout << endl;
	rep(i,0,N-1) {
		if (i) cout << ' ';
		cout << R[i];
	}
	cout << endl;
}
