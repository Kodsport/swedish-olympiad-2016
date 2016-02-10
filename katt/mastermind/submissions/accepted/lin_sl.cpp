#include "mastermind.h"

void init(int N) {
	bool* g = new bool[N]();
	int cor = guess(g);
	for (int i = 0; i < N; i++) {
		g[i] = 1;
		int cor2 = guess(g);
		if (cor2 < cor) g[i] = 0;
		else cor = cor2;
	}
	delete[] g;
}
