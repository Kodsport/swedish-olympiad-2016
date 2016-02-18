#include <cstdio>
#include <cassert>
#include <tuple>
#include <vector>
#include <cstring>

using namespace std;

/*
 * This solution should solve test group 1 and get 7 points (at least).
 */

vector<int>* adj;
bool* done;
int* owner;
int alternating_path(int left) {
    if (done[left]) return 0;
    done[left] = true;
    for (size_t i = 0; i < adj[left].size(); i++) {
        int right = adj[left][i];
        if (owner[right] == -1 || alternating_path(owner[right])) {
            owner[right] = left; return 1;
        }
    }
    return 0;
}

int tshirt(int N, int L[], int H[], int T[]) {
    adj = new vector<int>[N];
    done = new bool[N];
    owner = new int[N];

    int ans = 0;
    for (int i = 0; i < N; i++) {
        owner[i] = -1;
        for (int j = 0; j < N; j++) {
            if (L[i] <= T[j] && T[j] <= H[i]) {
                adj[i].push_back(j);
            }
        }
    }

    for (int i = 0; i < N; i++) {
        memset(done, 0, sizeof(bool) * N);
        ans += alternating_path(i);
    }

    delete[] adj;
    delete[] done;
    delete[] owner;
    return ans;
}

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
