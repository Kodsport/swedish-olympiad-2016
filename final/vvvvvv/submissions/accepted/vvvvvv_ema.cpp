#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < int(b); i++)
#define trav(it, v) for(auto it = v.begin(); it != v.end(); it++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x).size()
 
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int> > vvi; 
 
vector<vector<bool> > vBlock(105, vector<bool>(105, false));
vector<vector<bool> > hBlock(105, vector<bool>(105, false));

void addVer(int x, int y1, int y2) {
	if (y1 > y2) swap(y1, y2);
	rep(y, y1, y2) {
		hBlock[x][y] = true;
	}
}

void addHor(int y, int x1, int x2) {
	if (x1 > x2) swap(x1, x2);
	rep(x, x1, x2) {
		vBlock[x][y] = true;
	}
}

void addLine(int x1, int y1, int x2, int y2) {
	if (x1 == x2) {
		addVer(x1, y1, y2);
	} else {
		addHor(y1, x1, x2);
	}
}

vvi nextUp(105, vi(105, -1)), nextDown(105, vi(105, -1));

void initGrav(int w, int h) {
	rep(x, 0, w+1) {
		int nD = -1, nU = -1;
		rep(y, 0, h+1) {
			if (vBlock[x][y]) nD = y;
			nextDown[x][y] = nD;
			nextUp[x][h-y] = nU;
			if (vBlock[x][h-y]) nU = h-y-1;
		}
	}
} 

struct State {
	int x, y, g;
	State(int x, int y, int g): x(x), y(y), g(g) {}
};

State bad(-1, -1, -1);
State makeMove(State s, int move) { // V = 0, H = 1, G = 2
	if (s.g == 0) {
		if (move == 0) { // move left
			if (s.x == 0 || hBlock[s.x][s.y] || nextDown[s.x-1][s.y] == -1) {
				return bad;
			}
			return State(s.x-1, nextDown[s.x-1][s.y], s.g);
		} else if (move == 1) { // move right
			if (hBlock[s.x+1][s.y] || nextDown[s.x+1][s.y] == -1) {
				return bad;
			}
			return State(s.x+1, nextDown[s.x+1][s.y], s.g);
		} else if (move == 2) { // change gravity
			if (nextUp[s.x][s.y] == -1) {
				return bad;
			}
			return State(s.x, nextUp[s.x][s.y], 1);
		}
	} else {
		if (move == 0) { // move left
			if (s.x == 0 || hBlock[s.x][s.y] || nextUp[s.x-1][s.y] == -1) {
				return bad;
			}
			return State(s.x-1, nextUp[s.x-1][s.y], s.g);
		} else if (move == 1) { // move right
			if (hBlock[s.x+1][s.y] || nextUp[s.x+1][s.y] == -1) {
				return bad;
			}
			return State(s.x+1, nextUp[s.x+1][s.y], s.g);
		} else if (move == 2) { // change gravity
			if (nextDown[s.x][s.y] == -1) {
				return bad;
			}
			return State(s.x, nextDown[s.x][s.y], 0);
		}
	
	}
	return bad;
}

int lastMove[105][105][2];
int prevX[105][105][2], prevY[105][105][2], prevG[105][105][2];
bool vis[105][105][2];

int main() {
	memset(vis, 0, sizeof(vis));
	memset(lastMove, -1, sizeof(vis));
	memset(prevX, -1, sizeof(vis));
	memset(prevY, -1, sizeof(vis));
	memset(prevG, -1, sizeof(vis));
	int W, H, N;
	cin >> W >> H >> N;
	rep(i, 0, N) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		addLine(x1, y1, x2, y2);
	}
	initGrav(W, H);


	queue<State> q;
	q.push(State(0, 0, 0));
	vis[0][0][0] = true;
	State end = bad;
	while(!q.empty()) {
		State s = q.front();
		q.pop();

		if (s.x == W-1 && s.y == H-1) {
			end = s;
			break;
		}

		rep(m, 0, 3) {
			State t = makeMove(s, m);
			if (t.x == -1) continue;
			if (vis[t.x][t.y][t.g]) continue;
			vis[t.x][t.y][t.g] = true;
			lastMove[t.x][t.y][t.g] = m;
			prevX[t.x][t.y][t.g] = s.x;
			prevY[t.x][t.y][t.g] = s.y;
			prevG[t.x][t.y][t.g] = s.g;
			q.push(t);
		}
	}

	if (end.x == -1) {
		cout << "Inte" << endl;
		return 0;
	}

	char move[3] = {'V', 'H', 'G'};
	int x = end.x, y = end.y, g = end.g;
	vector<char> ans;
	while (!(x == 0 && y == 0 && g == 0)) {
		ans.push_back(move[lastMove[x][y][g]]);
		int nx = prevX[x][y][g];
		int ny = prevY[x][y][g];
		int ng = prevG[x][y][g];
		x = nx;
		y = ny;
		g = ng;
	}
	for (int i = ans.size()-1; i >= 0; i--) {
		cout << ans[i];
	}
	cout << endl;
}
