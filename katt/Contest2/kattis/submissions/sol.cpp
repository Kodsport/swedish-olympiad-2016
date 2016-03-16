#include "accepted/simon/kattis.cpp"

int main() {
	int N, H;
	ignore = scanf("%d%d", &N, &H);
	int X[N], Y[N], Z[N];
	for (int i = 0; i < N; i++) {
		ignore = scanf("%d", X + i);
		ignore = scanf("%d", Y + i);
		ignore = scanf("%d", Z + i);
	}
	printf("%d\n", kattis(N,H,X,Y,Z));
}
