#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;

typedef pair<int,int> pii;
typedef pair<long long, int> pli;

struct UnionFind {
	vector<int> data;

	UnionFind(int n) : data(n, -1) {
	}

	int find (int x) {
		if (data[x] < 0) return x;
		return data[x] = find(data[x]);
	}

	void join (int a, int b) {
		a = find(a);
		b = find(b);
		if (data[a] > data[b]) {
			swap(a,b);
		}
		data[a] += data[b];
		data[b] = a;
	}

	bool same (int a, int b) {
		return find(a) == find(b);
	}
};

int main () {
	long long n, k;
	cin >> n >> k;

	UnionFind uf(n);
	map<long long,set<pli>> buildings;
	for (int i = 0; i < n; i++) {
		long long x, y;
		cin >> x >> y;
		buildings[x].insert(pli(y, i));
	}

	priority_queue<pair<int,pii>> que;

	for (auto colpair : buildings) {
		int x = colpair.first;
		auto col = colpair.second;
		for (auto it = col.begin(); it != col.end(); it++) {
			auto j = it;
			j++;
			// Highest y coordinate that will belong to this shadow
			auto top = j != col.end() ? (*j).first - 1 : 1LL << 62;
			auto bottom = (*it).first;
			auto id = (*it).second;

			//cout << bottom << " " << top << endl;

			if (top - bottom == 0) continue;

			if (buildings.find(x-1) != buildings.end()) {
				auto othercol = buildings[x-1];
				auto lowest = othercol.upper_bound(pli(bottom, -1));
				if (lowest != othercol.begin()) lowest--;

				auto highest = othercol.lower_bound(pli(top, -1));
				for (; lowest != highest; lowest++) {
					auto otherid = (*lowest).second;
					auto otherbottom = (*lowest).first;
					auto timeToReach = abs(otherbottom - bottom);
					//cout << "Time to reach " << otherbottom << " from " << bottom << " " << timeToReach << endl;
					que.push(pair<int, pii>(-timeToReach, pii(id, otherid)));
				}
			}
		}
	}

	if (uf.same(0, n-1)) {
		cout << 0 << endl;
		return 0;
	} else {
		while (!que.empty()) {
			auto pair = que.top();
			auto buildingpair = pair.second;
			auto t = -pair.first;
			que.pop();
			uf.join(buildingpair.first, buildingpair.second);
			if (uf.same(0, n-1)) {
				if (t >= k) {
					break;
				}
				cout << t << endl;
				return 0;
			}
		}
	}

	cout << "NATT" << endl;
	return 0;
}
