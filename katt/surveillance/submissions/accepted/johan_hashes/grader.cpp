#include "surveillance.h"
#include <bits/stdc++.h>

using namespace std;

int main() {
	int B, W;
	ignore = scanf("%d%d", &B, &W);
  int S[1000][1000], T[1000][1000];
  for (int i = 0; i < B; ++i) for (int j = 0; j < B; ++j) ignore = scanf("%d", &S[i][j]);
  for (int i = 0; i < W; ++i) for (int j = 0; j < W; ++j) ignore = scanf("%d", &T[i][j]);
  printf("%d\n", surveillance(B, W, S, T));
}
