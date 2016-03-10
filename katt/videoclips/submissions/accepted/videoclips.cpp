#include "videoclips.h"

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
    nx[j] = j;
    for (int i = 1; i < 32; ++i) {
      if (M & 1) {
        nx[j] = jmp[i][nx[j]];
      }
      M /= 2;
    }
  }
}

int clip(int I) {
  return nx[I];
}
