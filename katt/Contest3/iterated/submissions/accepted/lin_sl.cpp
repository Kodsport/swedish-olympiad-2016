#include "iterated.h"

void init(int N) {
	int* g = new int[N]();
	int cor = guess(g);
	for (int i = 0; i < N; i++) {
		g[i] = 1;
		int cor2 = guess(g);
		if (cor2 < cor) g[i] = 0;
		else cor = cor2;
	}
	delete[] g;
}
