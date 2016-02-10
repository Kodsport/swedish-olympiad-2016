#include "mastermind.h"

void init(int N) {
	bool* ar = new bool[N]();
	guess(ar);
	ar[0] = ar[1] = ar[2] = 1;
	guess(ar);
}
