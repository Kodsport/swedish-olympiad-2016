#include "mafia.h"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<int>> calls;

void part(int S, int R[]) {
	calls.emplace_back(R, R + S);
}

int main() {
	int N, M;
	ignore = scanf("%d%d", &N, &M);
	int A[M], B[M], T[M];
	for (int i = 0; i < M; i++) ignore = scanf("%d", A + i);
	for (int i = 0; i < M; i++) ignore = scanf("%d", B + i);
	for (int i = 0; i < M; i++) ignore = scanf("%d", T + i);
	int G;
	ignore = scanf("%d", &G);
	int C[G];
	for (int i = 0; i < G; i++) ignore = scanf("%d", C + i);
	cops(N, M, A, B, T);
	for (int i = 0; i < G; ++i) {
		printf("%lld",  guess(C[i]));
		if (i != G-1) putchar(' ');
	}
	printf("\n");
}
