#include "friends.h"
#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

typedef long long ll;

set<int> occ;
int len;

void init(int N, int L, int* P) {
    len = L;
    for (int i = 0; i < N; i++) occ.insert(P[i]);
}

void jump(int A, int B) {
    occ.erase(A);
    occ.insert(B);
}

ll score() {
    ll x = 0, u = 0;
    int v = -2;
    for (auto p : occ) {
        if (p == v+1) {
            u++;
        } else {
            x += u*u;
            u = 1;
        }
        v = p;
    }
    x += u*u;
    return x;
}
