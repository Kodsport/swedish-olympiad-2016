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
		printf("fail, %d tricks", (int)output.size());
	} else {
		printf("%d\n", sol);
		for (int i = 0; i < N; i++)
			printf("%d ", output[i]);
		puts("");
	}
}
