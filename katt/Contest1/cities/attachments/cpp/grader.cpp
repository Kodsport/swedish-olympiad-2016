#include "cities.h"
#include <iostream>
using namespace std;

int main() {
    int N, K;
    cin >> N >> K;
    int F[N], T[N];
    for (int i = 0; i < N-1; i++) cin >> F[i];
    for (int i = 0; i < N-1; i++) cin >> T[i];
    cout << paths(N,K,F,T) << "\n";
}
