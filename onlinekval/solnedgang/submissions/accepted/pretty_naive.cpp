#include <iostream>
#include <vector>
#include <stack>

using namespace std;
typedef pair<long long,long long> pii;


vector<vector<int>> city;
vector<vector<int>> lastSeen;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int sizex;
int sizey;

int dfs (pii start, pii end, int t) {
	stack<pii> st;
	lastSeen[start.first][start.second] = t;
	st.push(start);

	while (!st.empty()) {
		auto node = st.top();
		st.pop();

		//cout << "Reached " << node.first << ", " << node.second << endl;
		if (node == end) {
			return true;
		}

		for (int i = 0; i < 4; i++) {
			int nx = node.first + dx[i];
			int ny = node.second + dy[i];
			if (nx >= 0 && ny >= 0 && nx < sizex && ny < sizey && city[nx][ny] == 1 && lastSeen[nx][ny] != t) {
				lastSeen[nx][ny] = t;
				st.push(pii(nx,ny));
			}
		}
	}

	return false;
}

int main () {
	int n, k;
	cin >> n >> k;

	pii mn (0,0);
	pii mx (0,0);
	vector<pii> houses(n);
	for (int i = 0; i < n; i++) {
		long long x, y;
		cin >> x >> y;
		houses[i].first = x;
		houses[i].second = y;
		mn.first = min(mn.first, x);
		mn.second = min(mn.second, y);
		mx.first = max(mx.first, x);
		mx.second = max(mx.second, y);
	}

	sizex = mx.first - mn.first + 5;
	sizey = mx.second - mn.second + 5;
	int tmax = min(sizey + 2,k);
	sizey += tmax;

	if (sizex*sizey > 10000*100000) return 1;

	city = vector<vector<int>>(sizex, vector<int>(sizey, 0));
	lastSeen = vector<vector<int>>(sizex, vector<int>(sizey, -1));

	for (int i = 0; i < n; i++) {
		houses[i].first -= mn.first;
		houses[i].second -= mn.second;
	}

	for (int i = 0; i < n; i++) {
		// cout << houses[i].first << " " << houses[i].second << " " << sizex << " " << sizey << endl;
		city[houses[i].first][houses[i].second] = -1;
	}

	for (int t = 0; t <= tmax; t++) {
		//cout << "T: " << t << endl;
		//cerr << t << endl;
		//cout << t << endl;
		for (int i = 0; i < n; i++) {
			// Don't overwrite exiting houses
			if (city[houses[i].first][houses[i].second+1+t] == 0) {
				city[houses[i].first][houses[i].second+1+t] = 1;
			}
		}

		if (dfs(pii(houses[0].first, houses[0].second+1), pii(houses[n-1].first, houses[n-1].second+1), t)) {
			if (t >= k) {
				break;
			}
			cout << t << endl;
			return 0;
		}
	}

	cout << "NATT" << endl;
	return 0;
}
