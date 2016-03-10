#include "invigilation.h"
#include <bits/stdc++.h>

using namespace std;

int main() {
	int N, H;
	ignore = scanf("%d%d", &N, &H);
	int X[N], Y[N], Z[N];
	for (int i = 0; i < N; i++) {
		ignore = scanf("%d", X + i);
		ignore = scanf("%d", Y + i);
		ignore = scanf("%d", Z + i);
	}
	printf("%d\n", invigilation(N,H,X,Y,Z));
}
