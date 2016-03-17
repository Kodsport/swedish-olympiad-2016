#include "fibonacci.h"
#include <bits/stdc++.h>

using namespace std;

int main() {
	int N;
	ignore = scanf("%d", &N);
  char X[N + 1];
  ignore = scanf("%d", &X);
  assert(strlen(X) == N);
	printf("%lld\n", fibonacci(N,X));
}
