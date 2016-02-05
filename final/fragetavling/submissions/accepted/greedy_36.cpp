#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < int(to); ++i)
#define trav(a, x) for (auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
void PR(vi &v) { trav(x, v) cout << x << ' '; cout << endl; }

int main() {
	cin.sync_with_stdio(false);
	int N, M, K, B;
	cin >> N >> M >> K >> B;
	vector<vi> cats(M);
	rep(i,0,N) {
		int pnt, cat;
		cin >> pnt >> cat;
		cats[cat-1].push_back(pnt);
	}
	vector<pair<double, pii>> pqcat;
	rep(i,0,M) {
		auto& cat = cats[i];
		int sum = 0;
		trav(x, cat) sum += x;
		double heuristic = (sum + B) / (double)sz(cat);
		pqcat.emplace_back(heuristic, pii(sum + B, i));
	}
	sort(all(pqcat));
	int avail = K;
	int bonus = 0;
	int res = 0;
	vi used(M);
	rep(i,0,M+1) {
		vi pq;
		pq.reserve(N);
		rep(j,0,M) {
			if (used[j]) continue;
			trav(x, cats[j])
				pq.push_back(x);
		}
		sort(all(pq), greater<int>());
		int a = avail, sol = 0;
		trav(y, pq) {
			if (!a) break;
			a--;
			sol += y;
		}
		res = max(res, sol + bonus);
		if (i != M) {
			int c = pqcat[M-1 - i].second.second;
			if (avail - sz(cats[c]) < 0) continue;
			avail -= sz(cats[c]);
			used[c] = true;
			bonus += pqcat[M-1 - i].second.first;
		}
	}
	cout << res << endl;
}
