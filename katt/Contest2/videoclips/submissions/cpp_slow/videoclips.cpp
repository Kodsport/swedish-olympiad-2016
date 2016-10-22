#include <map>
using namespace std;
#include "videoclips.h"

int nx[100000];
int steps;

void videos(int K, int M, int S[]) {
  for (int i = 0; i < K; i++) nx[i] = S[i];
  steps = M % 1000;
}

int clip(int I) {
  map<int, int> seen;
  for (int i = 0; i < steps - 1; ++i) {
    I = nx[I];
    seen[I] = i;
  }
  return I;
}
