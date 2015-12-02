#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;

typedef pair<int,int> pii;
typedef pair<long long,long long> pll;
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
		if (a == b) return;

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
	map<long long,set<long long>> buildings;
	map<pll, int> buildingIDs;

	for (int i = 0; i < n; i++) {
		long long x, y;
		cin >> x >> y;
		buildings[x].insert(y);
		buildingIDs[pll(x,y)] = i;
	}

	priority_queue<pair<long long, pii>> que;

	// Loop through all columns
	for (auto& colpair : buildings) {
		auto x = colpair.first;
		auto& col = colpair.second;

		// Loop through all buildings in column
		for (auto it = col.begin(); it != col.end(); it++) {
			// Next building
			auto j = it;
			j++;
			auto y = *it;

			// Highest y coordinate that will belong to this shadow
			auto top = j != col.end() ? (*j) - 1 : 1LL << 62;
			// Lowest y coordinate that will beong to this shadow
			auto bottom = y + 1;

			// Id of the building
			auto id = buildingIDs[pll(x,y)];

			// Ignore buildings with no shadows
			// (not required by problem statement anymore)
			if (top - bottom < 0) continue;

			// Check if a column to the left exists
			if (buildings.find(x-1) != buildings.end()) {
				auto& othercol = buildings[x-1];

				// (Smallest Y > bottom)-1 == Greatest Y <= bottom
				auto lowest = othercol.upper_bound(bottom);
				if (lowest != othercol.begin()) lowest--;

				// (Smallest Y >= top)-1 == Greatest Y < top
				auto highest = othercol.lower_bound(top);

				// Loop through all buildings (shadows) that we
				// can move to from this shadow
				for (; lowest != highest; lowest++) {
					auto otherY = *lowest;
					auto otherid = buildingIDs[pll(x-1, otherY)];
					auto otherbottom = otherY + 1;
					auto timeToReach = abs(otherbottom - bottom);

					// Add an edge to that shadow
					// - since it is a max heap, not a min heap
					que.push(pair<long long, pii>(-timeToReach, pii(id, otherid)));
				}
			}
		}
	}

	// If n == 1 this will happen
	if (uf.same(0, n-1)) {
		cout << 0 << endl;
		return 0;
	} else {

		// Process events in chronological order
		// Stop when we can reach the target
		while (!que.empty()) {

			auto pair = que.top();
			auto buildingpair = pair.second;
			auto t = -pair.first;
			que.pop();
			uf.join(buildingpair.first, buildingpair.second);

			// Can we reach the target
			if (uf.same(0, n-1)) {
				cout << t << endl;
				return 0;
			}
		}
	}

	cout << "NATT" << endl;
	return 0;
}
