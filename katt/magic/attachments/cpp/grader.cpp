#include "magic.h"
#include <cstdio>
#include <cassert>
#include <tuple>
#include <vector>

using namespace std;

static std::vector<int> output;
void trick(int rabbits) {
	output.push_back(rabbits);
}

int main() {
	int N, K;
	ignore = scanf("%d%d", &N, &K);
	std::vector<int> L(N), R(N);
	for (int i = 0; i < N; i++)
		ignore = scanf("%d", &L[i]);
	for (int i = 0; i < N; i++)
		ignore = scanf("%d", &R[i]);
	output.reserve(N);
	int sol = magic_score(N, K, L.data(), R.data());
	if ((int)output.size() != N) {
		printf("error: tried to perform %d tricks, should perform %d", (int)output.size(), N);
	} else {
		printf("%d\n", sol);
		for (int i = 0; i < N; i++) {
			if (i != 0) putchar(' ');
			printf("%d", output[i]);
		}
		puts("");
	}
}
