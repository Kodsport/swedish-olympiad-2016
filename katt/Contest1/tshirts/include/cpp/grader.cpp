#include "tshirts.h"
#include <cstdio>
#include <cassert>
#include <tuple>

using namespace std;

int inputL[100000],
    inputH[100000],
    inputT[100000];

int main() {
    int N;
    ignore = scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        ignore = scanf("%d", &inputL[i]);
    }
    for (int i = 0; i < N; ++i) {
        ignore = scanf("%d", &inputH[i]);
    }
    for (int i = 0; i < N; ++i) {
        ignore = scanf("%d", &inputT[i]);
    }
    printf("%d\n", tshirt(N, inputL, inputH, inputT));
}
