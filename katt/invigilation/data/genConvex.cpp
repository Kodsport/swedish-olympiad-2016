// Generates convex input.
// params: N seed

#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < int(b); i++)
#define trav(it, v) for(auto it = v.begin(); it != v.end(); it++)
#define all(x) x.begin(), x.end()
typedef pair<int, int> pii;

int main(int argc, char* argv[]) {
	if (argc < 3) {
		cerr << "Error: not enough arguments" << endl;
		return 0;
	}
	int N = atoi(argv[1]);
	int seed = atoi(argv[2]);
	assert(N <= 100000);
	N -= 2;
	srand(seed);

	vector<pair<double, pii> > ps;
	int sumy = 0;
	while (sumy <= 0) {
		sumy = 0; ps.clear();
		rep(i,0,N) {
			int x = rand() % 13 + 1;
			int y = rand() % 13;
			if (rand() & 128) y = -y;
			ps.emplace_back(-y / (double)x, pii(y, x));
			sumy += y;
		}
	}
	sort(all(ps), [](auto a, auto b) { return a.first < b.first; });
	int cury = 0, curx = 120;
	vector<pii> pt = {pii(curx, 0)};
	rep(i,0,N) {
		pii pa;
		int y, x;
		tie(ignore, pa) = ps[i];
		tie(y, x) = pa;
		cury += y;
		curx += x;
		pt.emplace_back(curx, cury);
	}
	pt.push_back(pii(curx+1, 0));

	int H = 1000000;
	cout << N+2 << ' ' << H << endl;
	rep(i,0,N+2) {
		int x, y;
		tie(x, y) = pt[i];
		int z = !!(rand() & 192);
		cout << x << ' ' << y << ' ' << z << endl;
	}
}
