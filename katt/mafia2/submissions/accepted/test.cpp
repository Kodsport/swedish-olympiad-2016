#include <bits/stdc++.h>

using namespace std;

int main() {
  int N, M;
  cin >> N >> M;
  vector<int> A(M), B(M), C(M);
  for (int i = 0; i < M; ++i) { cin >> A[i]; }
  for (int i = 0; i < M; ++i) { cin >> B[i]; }
  for (int i = 0; i < M; ++i) { cin >> C[i]; }
  vector<int> colors(N);
  srand(time(NULL));
  for(int i = 0; i < N; ++i) {
    colors[i] = rand()%2;
  }
  for(int i = 0; i < M; ++i) {
    int d = 1 - C[i];
    assert(A[i] <= N);
    assert(B[i] <= N);
    printf("%d ", (colors[A[i]] ^ d) == colors[B[i]]);
  }
  printf("\n");
}
