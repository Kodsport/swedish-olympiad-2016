#include "accepted/simon/kingdom.cpp"

void parts(int R[]) {}

int main() {
	int N, P;
	ignore = scanf("%d%d", &N, &P);
	int C[N], F[N - 1], T[N - 1];
	for (int i = 0; i < N; i++) ignore = scanf("%d", C + i);
	for (int i = 0; i < N-1; i++) ignore = scanf("%d", F + i);
	for (int i = 0; i < N-1; i++) ignore = scanf("%d", T + i);
	printf("%d\n", division(N,P,C,F,T));
}
