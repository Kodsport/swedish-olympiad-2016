#include "magic.h"
using namespace std;

int magic_score(int N, int K, int L[], int R[]) {
	int res = 0;
	for (int i = 0; i < N; i++) {
		res += (R[i] - L[i]) / 2;
		trick(0);
	}
	return res;
}
