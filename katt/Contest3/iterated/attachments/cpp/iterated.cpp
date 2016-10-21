#include "iterated.h"

void init(int N) {
	int* ar = new int[N]();
	guess(ar);
	ar[0] = ar[1] = ar[2] = 1;
	guess(ar);
}
