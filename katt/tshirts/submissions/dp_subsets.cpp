#include <cstdio>
#include <cassert>
#include <tuple>
#include <vector>

using namespace std;

/*
 * This solution should only solve test group 1, and get 7
 * points.
 */

int dp[12][1<<12];

int tshirt(int N, vector<int> L, vector<int> H, vector<int> T) {

    for (int at = N; at >= 0; at--) {
        for (int rem = 0; rem < (1<<N); rem++) {
            if (at == N) {
                dp[at][rem] = 0;
            } else {
                dp[at][rem] = dp[at+1][rem];
                for (int mat = 0; mat < N; mat++) {
                    if ((rem & (1<<mat)) && L[at] <= T[mat] && T[mat] <= H[at]) {
                        dp[at][rem] = max(dp[at][rem], 1 + dp[at+1][rem & ~(1<<mat)]);
                    }
                }
            }
        }
    }

    return dp[0][(1<<N)-1];
}

int main() {
    int N;
    ignore = scanf("%d", &N);
    vector<int> L(N), H(N), T(N);
    for (int i = 0; i < N; ++i) {
        ignore = scanf("%d", &L[i]);
    }
    for (int i = 0; i < N; ++i) {
        ignore = scanf("%d", &H[i]);
    }
    for (int i = 0; i < N; ++i) {
        ignore = scanf("%d", &T[i]);
    }
    printf("%d\n", tshirt(N, L, H, T));
}
