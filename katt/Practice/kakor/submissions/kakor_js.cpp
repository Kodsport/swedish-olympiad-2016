#include <cstdio>

long long cookies(int N, int A[]) {
  long long ans = 0;
  for (int i = 0; i < N; ++i) ans += A[i];
  return ans;
}

int main() {
  int N;
  scanf("%d", &N);
  int A[N];
  for (int i = 0; i < N; ++i) scanf("%d", A + i);
  printf("%lld\n", cookies(N, A));
}
