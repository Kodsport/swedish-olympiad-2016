#include "vanner.h"
#include <set>

using namespace std;

int sc;
set<int> pos;

void init(int N, int L, int P[]) {
  for (int i = 0; i < N; ++i) jump(-100, P[i]);
}

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

int score(){
  return sc;
}
