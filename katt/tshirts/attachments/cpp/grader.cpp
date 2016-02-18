#include "tshirts.h"
#include <cstdio>
#include <cassert>
#include <tuple>
#include <vector>

using namespace std;

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
