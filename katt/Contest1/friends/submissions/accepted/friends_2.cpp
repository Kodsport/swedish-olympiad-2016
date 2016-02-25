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
    ll x = 0, u = 0;
    for (int i = 0; i < len; i++) {
        if (occ[i]) u++;
        else u = 0;
        if (i == len-1 || !occ[i+1]) {
            x += u*u;
        }
    }
    return x;
}
