#include <cstdio>
#include <cassert>
#include <tuple>
#include <vector>

using namespace std;

/*
 * This solution should only solve test group 3, and get 13
 * points.
 */

int tshirt(int N, vector<int> L, vector<int> H, vector<int> T) {
    int ans = 0;
    int cnt[2];
    cnt[0] = cnt[1] = 0;
    for (int i = 0; i < N; i++) {
        cnt[T[i]]++;
    }
    for (int i = 0; i < N; i++) {
        if (L[i] == H[i] && cnt[L[i]] > 0) {
            cnt[L[i]]--;
            ans++;
        }
    }
    for (int i = 0; i < N; i++) {
        if (L[i] != H[i]) {
            if (cnt[L[i]] > 0) {
                cnt[L[i]]--;
                ans++;
            } else if (cnt[H[i]] > 0) {
                cnt[H[i]]--;
                ans++;
            }
        }
    }
    return ans;
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
