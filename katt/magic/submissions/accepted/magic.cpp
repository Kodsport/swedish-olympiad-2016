#include <bits/stdc++.h>
#include "magic.h"
using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
#define rep(i,f,t) for (int i = f; i < t; ++i)

int magic_score(int N, int K, int L[], int R[]) {
	priority_queue<pii, vector<pii>, greater<pii> > ds;
	int greedy = 0, freeGreedy = 0;
	vector<vector<bool>> useds;
	vi dp(K+1), ord, dists;
	vector<bool> used;
	rep(t,0,N) {
		int r = R[t], l = L[t];
		if (l <= 0 && 0 <= r) {
			greedy += min(-l, r);
			freeGreedy += abs((l + r) / 2);
		}
		else {
			int dist = min(abs(l), abs(r));
			int val = (r - l) / 2;
			if (dist <= K) {
				used.assign(K+1, false);
				for (int i = K; i >= 0; i--) {
					int j = i - dist;
					if (j < 0) break;
					if (dp[j] + val > dp[i]) {
						dp[i] = dp[j] + val;
						used[i] = true;
					}
				}
				useds.push_back(used);
				ord.push_back(t);
				dists.push_back(dist);
			}
		}
	}
	int best = -1, besti = -1;
	rep(i,0,K+1) {
		int val = dp[i] + min(K-i, greedy) + freeGreedy;
		if (val > best) {
			best = val;
			besti = i;
		}
	}

	vi shouldUse(N);

	int nu = (int)useds.size();
	int curi = besti;
	rep(i,0,nu) {
		const vector<bool>& used = useds[nu-1 - i];
		int di = dists[nu-1 - i];
		int t = ord[nu-1 - i];
		if (used[curi]) {
			curi -= di;
			shouldUse[t] = 1;
		}
	}
	assert(curi == 0);
	int gr = K - besti;

	int totscore = 0;
	rep(t,0,N) {
		int r = R[t], l = L[t];
		if (l <= 0 && 0 <= r) {
			int g = min(gr, min(-l, r));
			gr -= g;
			// move g steps towards right or left
			int x = (l+r <= 0 ? g : -g);
			assert(l <= x && x <= r);
			trick(x);
			totscore += abs((l + r) / 2 - x);
		} else if (shouldUse[t]) {
			int x = (l <= r ? l : r);
			trick(x);
			totscore += abs((l + r) / 2 - x);
		} else {
			trick(0);
		}
	}

	assert(totscore == best);

	return best;
}
