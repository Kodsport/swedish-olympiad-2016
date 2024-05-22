#include "friends.h"
#include <cstdio>
#include <cassert>

int main() {
  int N, L, Q;
  scanf("%d%d%d", &N, &L, &Q);
  int P[N];
  for (int i = 0; i < N; ++i) scanf("%d", P + i);
  init(N, L, P);
  for (int i = 0; i < Q; ++i) {
    int type;
    scanf("%d", &type);
    if (type == 0) {
      int A, B;
      scanf("%d%d", &A, &B);
      jump(A, B);
    }
    else if (type == 1) printf("%lld\n", score());
    else assert(false && "Invalid query type");
  }
}
