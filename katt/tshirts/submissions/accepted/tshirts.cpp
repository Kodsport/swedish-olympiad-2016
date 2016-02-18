#include <vector>
#include <cstdio>
#include <cassert>
#include <tuple>
#include <queue>
#include <algorithm>

using namespace std;

int tshirt(int N, vector<int> L, vector<int> H, vector<int> T) {
    vector<pair<int,int> > ev;
    for (int i = 0; i < N; i++) {
        ev.push_back(make_pair(L[i], -H[i]));
        ev.push_back(make_pair(T[i], 1));
    }
    sort(ev.begin(), ev.end());
    priority_queue<int, vector<int>, greater<int> > pq;
    int ans = 0;
    for (size_t i = 0; i < ev.size(); i++) {
        if (ev[i].second == 1) {
            while (!pq.empty() && pq.top() < ev[i].first) {
                pq.pop();
            }
            if (!pq.empty()) {
                ans++;
                pq.pop();
            }
        } else {
            pq.push(-ev[i].second);
        }
    }
    return ans;
}
