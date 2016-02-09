#include <vector>
#include <cstdio>
#include <cassert>
#include <tuple>

using namespace std;

vector<int> num(10000000);

int arrtonum(int P[6]){
	int x = 0;
	for (int i = 0; i < 6; ++i) {
		x = 11 * x + (P[i] + 1);
	}
	return x;
}

int plate(int P[6]) {
	int ans = num[arrtonum(P)];
	int p[6];
	for (int i = 0; i < (1 << 6); i++) {
		for (int j = 0; j < 6; ++j) {
			if (i & (1 << j)) {
				if (P[j] == -1) goto skip;
				p[j] = -1;
			} else p[j] = P[j];
		}
		num[arrtonum(p)]++;
skip:;
	}
	return ans;
}


int main() {
  int N;
  ignore = scanf("%d", &N);
  int P[6];
  for (int i = 0; i < N; ++i) {
	  for (int j = 0; j < 6; ++j) {
		  ignore = scanf("%d", P + j);
	  }
	  printf("%d\n", plate(P));
  }
}
