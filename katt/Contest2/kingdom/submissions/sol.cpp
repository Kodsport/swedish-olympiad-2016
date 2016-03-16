#include "accepted/simon/kingdom.cpp"

int N, P;
vector<int> calls;

void parts(int R[]) {
	calls.assign(R, R + N);
}

int main() {
	ignore = scanf("%d%d", &N, &P);
	calls.resize(N);
	int C[N], F[N - 1], T[N - 1];
	for (int i = 0; i < N; i++) ignore = scanf("%d", C + i);
	for (int i = 0; i < N-1; i++) ignore = scanf("%d", F + i);
	for (int i = 0; i < N-1; i++) ignore = scanf("%d", T + i);
	int ret = division(N,P,C,F,T);
	printf("%d\n", ret);
	if (ret) {
		for (int i = 0; i < N; ++i) {
			printf("%d", calls[i]);
			if (i != N-1) putchar(' ');
		}
		puts("");
	}
}
