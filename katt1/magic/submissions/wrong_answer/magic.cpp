#include <bits/stdc++.h>
#include "magic.h"
using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;

int magic_score(int N, int K, int L[], int R[]) {
	priority_queue<pii, vector<pii>, greater<pii> > ds;
	for (int i = 0; i < N; i++) {
		ds.push(pii(min(abs(L[i]), abs(R[i])), i));
	}
	int res = 0;
	vi incl(N);
	while (!ds.empty()) {
		auto pa = ds.top();
		ds.pop();
		if (pa.first <= K) {
			incl[pa.second] = 1;
			res++;
			K -= pa.first;
		}
	}
	// fail to call trick
    return res;
}
