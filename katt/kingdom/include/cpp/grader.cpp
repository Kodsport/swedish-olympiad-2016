#include "kingdom.h"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<int>> calls;

void parts(int S, int R[]) {
	calls.emplace_back(R, R + S);
}

int main() {
	int N, P;
	ignore = scanf("%d%d", &N, &P);
	int C[N], F[N - 1], T[N - 1];
	for (int i = 0; i < N; i++) ignore = scanf("%d", C + i);
	for (int i = 0; i < N-1; i++) ignore = scanf("%d", F + i);
	for (int i = 0; i < N-1; i++) ignore = scanf("%d", T + i);
	printf("%d\n", division(N,P,C,F,T));
	printf("%lu\n", calls.size());
	for (auto& it : calls) {
		printf("%lu", it.size());
		for (size_t i = 0; i < it.size(); i++) {
			if (i) printf(" ");
			printf("%d", it[i]);
		}
		printf("\n");
	}
}
