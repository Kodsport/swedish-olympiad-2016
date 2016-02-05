#include <cstdio>
#include <vector>
#include <algorithm>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)

using namespace std;

int main() {
	int N, M, K, B;
	scanf("%d %d %d %d", &N, &M, &K, &B);

	vector< vector<int> > categories(M);

	rep (i, 0, N) {
		int p, c;
		scanf("%d %d", &p, &c);
		categories[c-1].push_back(p);
	}

	rep (i, 0, M) {
		sort(categories[i].begin(), categories[i].end(), [](const int &a, const int &b) -> bool { return b < a; });
		for (int j = 1; j < categories[i].size(); j++) {
			categories[i][j] += categories[i][j-1];
		}
	}

	vector< vector<int> > dp(M+1, vector<int>(K+1, 0));

	rep (m, 1, M+1) {
		rep (k, 1, K+1) {
			rep (i, 0, categories[m-1].size() + 1) {
				if (k-i < 0) {
					break;
				}

				int inc = (i == 0) ? 0 : categories[m-1][i-1];
				if (i == categories[m-1].size()) {
					inc += B;
				}
				dp[m][k] = max(dp[m][k], dp[m-1][k-i] + inc);

			}
		}
	}

	printf("%d\n", dp[M][K]);
}
