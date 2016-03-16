#include "videoclips.h"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<int>> calls;

void part(int S, int R[]) {
	calls.emplace_back(R, R + S);
}

int main() {
	int K, M;
	ignore = scanf("%d%d", &K, &M);
	int S[K];
	for (int i = 0; i < K; i++) ignore = scanf("%d", S + i);
	videos(K, M, S);
  int N;
  ignore = scanf("%d", &N);
  for (int i = 0; i < N; ++i) {
    int X;
    ignore = scanf("%d", &X);
    printf("%d ",  clip(X));
  }
  printf("\n");
}
