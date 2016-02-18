#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
#define rep(i,f,t) for (int i = f; i < t; ++i)

static std::vector<int> output;
void trick(int rabbits) {
	output.push_back(rabbits);
}

int magic_score(int N, int K, int L[], int R[]) {
	// TODO write a proper solution
	priority_queue<pii, vector<pii>, greater<pii> > ds;
	rep(i,0,N) {
		if (R[i] - L[i] != 2) {
			cerr << "fail! at index " << i << endl;
			rep(j,0,N) trick(0);
			return 0;
		}
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
	rep(i,0,N) {
		if (!incl[i]) trick(0);
		else {
			int d = min(abs(L[i]), abs(R[i]));
			if (abs(L[i]) == d)
				trick(L[i]);
			else
				trick(R[i]);
		}
	}
    return res;
}

int main() {
	int N, K;
	ignore = scanf("%d%d", &N, &K);
	vi L(N), R(N);
	for (int i = 0; i < N; i++)
		ignore = scanf("%d", &L[i]);
	for (int i = 0; i < N; i++)
		ignore = scanf("%d", &R[i]);
	output.reserve(N);
	int sol = magic_score(N, K, L.data(), R.data());
	if ((int)output.size() != N) {
		printf("fail, %d tricks", (int)output.size());
	} else {
		printf("%d\n", sol);
		for (int i = 0; i < N; i++) {
			if (i != 0) putchar(' ');
			printf("%d", output[i]);
		}
		puts("");
	}
}
