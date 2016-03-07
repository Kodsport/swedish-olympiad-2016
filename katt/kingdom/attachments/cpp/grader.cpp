#include "kingdom.h"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, P;
vector<int> calls;

void parts(int R[]) {
	calls.assign(R, R + N);
}

int main() {
	ignore = scanf("%d%d", &N, &P);
	int C[N], F[N - 1], T[N - 1];
	for (int i = 0; i < N; i++) ignore = scanf("%d", C + i);
	for (int i = 0; i < N-1; i++) ignore = scanf("%d", F + i);
	for (int i = 0; i < N-1; i++) ignore = scanf("%d", T + i);
	printf("%d\n", division(N,P,C,F,T));
	for (int i = 0; i < N; ++i) {
		printf("%d ", calls[i]);
	}
}
