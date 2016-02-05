// Löser testfallsgrupp 3 (alla frågor ger lika mycket poäng)

#include <cstdio>
#include <vector>
#include <algorithm>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)

using namespace std;

int main() {
	int N, M, K, B;
	scanf("%d %d %d %d", &N, &M, &K, &B);

	vector<int> categories(M, 0);
	int qp = 0;

	rep (i, 0, N) {
		int c;
		scanf("%d %d", &qp, &c);
		categories[c-1]++;
	}

	int sum = K * qp;
	sort(categories.begin(), categories.end());

	int k = 0;
	rep (i, 0, M) {
		if (categories[i] <= (K - k)) {
			sum += B;
			k += categories[i];
		} else {
			break;
		}
	}

	printf("%d\n", sum);
}
