#include "kakor.h"
#include <cstdio>

int main() {
  int N;
  scanf("%d", &N);
  int A[N];
  for (int i = 0; i < N; ++i) scanf("%d", A + i);
  printf("%lld\n", cookies(N, A));
}
