#include "friends.h"
#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

typedef long long ll;

int occ[101010];
int len;

void init(int N, int L, int* P) {
    len = L;
    for (int i = 0; i < N; i++) occ[P[i]] = 1;
}

void jump(int A, int B) {
    occ[A] = 0;
    occ[B] = 1;
}

ll score() {
    ll x = 0;
    for (int i = 0; i < len; i++) {
        if (!occ[i]) continue;
        int u = 1;
        for (int j = i-1; j >= 0; j--) {
            if (!occ[j]) break;
            u++;
        }
        for (int j = i+1; j < len; j++) {
            if (!occ[j]) break;
            u++;
        }
        x += u;
    }
    return x;
}
