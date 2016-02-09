#include "regskylt.h"
#include <cstdio>
#include <cassert>
#include <tuple>

using namespace std;

int main() {
  int N;
  ignore = scanf("%d", &N);
  int P[6];
  for (int i = 0; i < N; ++i) {
	  for (int j = 0; j < 6; ++j) {
		  ignore = scanf("%d", P + j);
	  }
	  printf("%d\n", plate(P));
  }
}
