#include "vanner.h"
#include <cstdio>

int main() {
  int N, L, Q;
  scanf("%d", &N);
  int P[N];
  for (int i = 0; i < N; ++i) scanf("%d", A + i);
  init(N, L, P);
  for (int i = 0; i < Q; ++i) {
    int type;
    scanf("%d", &type);
    if (type == 0) {
      int A, B;
      scanf("%d%d", &A, &B);
      jump(A, B);
    }
    else if (type == 1) printf("%d", score());
    else assert(false && "Invalid query type");
  }
  printf("%lld\n", cookies(N, A));
}
