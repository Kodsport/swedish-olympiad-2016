#include <set>
#include <cassert>

using namespace std;

int sc;
set<int> pos;


bool in(int A) {
  return pos.find(A) != pos.end();
}

void jump(int A, int B) {
  if (in(A - 1) or in(A + 1)) sc--;
  if (in(A - 1) and not in(A - 2)) sc--;
  if (in(A + 1) and not in(A + 2)) sc--;
  pos.erase(A);

  if (in(B - 1) or in(B + 1)) sc++;
  if (in(B - 1) and not in(B - 2)) sc++;
  if (in(B + 1) and not in(B + 2)) sc++;
  pos.insert(B);
}

void init(int N, int L, int P[]) {
  for (int i = 0; i < N; ++i) jump(-100, P[i]);
}

int score(){
  return sc;
}

#include <cstdio>

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
    else if (type == 1) printf("%d\n", score());
    else assert(false && "Invalid query type");
  }
}
