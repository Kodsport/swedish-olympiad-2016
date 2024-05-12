#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < int(to); ++i)
#define trav(a, x) for (auto& a : x)
typedef pair<int, int> pii;
typedef vector<int> vi;

bool canmove(string& type, int x, int y, int x2, int y2) {
	int dx = abs(x - x2), dy = abs(y - y2);
	if (x == x2 && y == y2) return false;
	bool torn = ((dx == 0 && (y2 == 0 || y2 == 5)) || (dy == 0 && (x2 == 0 || x2 == 5)));
	bool lop = (dx == dy && (x2 == 0 || x2 == 5 || y2 == 0 || y2 == 5));
	if (isdigit(type[0])) {
		int d = type[0] - '0';
		assert(1 <= d && d <= 4);
		return ((dx == d || dx == 0) && (dy == d || dy == 0) && (dx || dy));
	}
	else if (type == "torn") return torn;
	else if (type == "lopare") return lop;
	else if (type == "dam") return torn || lop;
	else if (type == "springare") {
		if (dx > dy) swap(dx, dy);
		return dx == 1 && dy == 2;
	}
	else if (type == "any") return true;
	else assert(0);
}

int main() {
	cin.sync_with_stdio(false);
	vector<vi> rem(6, vi(6, 3));
	vector<vector<string>> types(6, vector<string>(6));
	rep(i,0,6) rep(j,0,6) {
		cin >> types[i][j];
	}
	int x = -1, y = -1;
	string attype = "any";
	for (;;) {
		vector<pii> m;
		rep(x2,0,6) rep(y2,0,6) {
			if (rem[y2][x2] && canmove(attype,x,y,x2,y2))
				m.emplace_back(y2, x2);
		}
		if (m.empty()) {
			cout << "0 0" << endl;
			return 0;
		}
		pii best = m[0];
		trav(x, m) {
			if (rem[x.first][x.second] > rem[best.first][best.second] ||
				(rem[x.first][x.second] == rem[best.first][best.second] && attype == types[x.first][x.second])) {
				best = x;
			}
		}
		y = best.first;
		x = best.second;
		cout << y+1 << ' ' << x+1 << endl;
		attype = types[y][x];
		cin >> types[y][x];
		--rem[y][x];
	}
}
