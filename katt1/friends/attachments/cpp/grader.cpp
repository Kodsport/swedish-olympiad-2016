#include "friends.h"
#include <cstdio>
#include <cassert>

int main() {
  int N, L, Q, ign;
  ign = scanf("%d%d%d", &N, &L, &Q);
  int P[N];
  for (int i = 0; i < N; ++i) ign = scanf("%d", P + i);
  init(N, L, P);
  for (int i = 0; i < Q; ++i) {
    int type;
    ign = scanf("%d", &type);
    if (type == 0) {
      int A, B;
      ign = scanf("%d%d", &A, &B);
      jump(A, B);
    }
    else if (type == 1) printf("%lld\n", score());
    else assert(false && "Invalid query type");
  }
  ign = ign;
}
