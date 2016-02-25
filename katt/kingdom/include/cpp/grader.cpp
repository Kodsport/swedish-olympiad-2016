#include "cities.h"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    int N, K;
	ignore = scanf("%d%d", &N, &K);
    int F[N - 1], T[N - 1];
    for (int i = 0; i < N-1; i++) scanf("%d", F + i);
    for (int i = 0; i < N-1; i++) scanf("%d", T + i);
	printf("%lld\n", paths(N,K,F,T));
}
