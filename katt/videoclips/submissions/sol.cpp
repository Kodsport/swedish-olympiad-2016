#include <bits/stdc++.h>
int jmp[32][100000];
int nx[100000];

void videos(int K, int M, int S[]) {
  for (int i = 0; i < K; i++) jmp[0][i] = S[i];
  for (int i = 1; i < 32; ++i) {
    for (int j = 0; j < K; ++j) {
      jmp[i][j] = jmp[i-1][jmp[i-1][j]];
    }
  }

  for (int j = 0; j < K; ++j) {
    int m = M - 1;
    nx[j] = j;
    for (int i = 0; i < 32; ++i) {
      if (m & 1) {
        nx[j] = jmp[i][nx[j]];
      }
      m /= 2;
    }
  }
}

int clip(int I) {
  return nx[I];
}


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
