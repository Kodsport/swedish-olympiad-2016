// Generates a single star.
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

	int K = 2;

	cout << N << ' ' << K << endl;
	vector<int> L, R;
	rep(i,0,N-1) {
		L.push_back(i+1);
		R.push_back(0);
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
