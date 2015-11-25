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

static pair<pii, pii> targetpos;
static int H, W;
static vector<string> board;

static bool oob(pii pos, bool toggleState) {
	if (pos.first < 0 || pos.second < 0) return true;
	if (pos.first >= H || pos.second >= W) return true;
	char c = board[pos.first][pos.second];
	if (c == '#') return true;
	if (c == '1') return !toggleState;
	if (c == '0') return toggleState;
	return false;
}

static bool dfs(pair<pii, pii> pos, int left, bool toggleState) {
	if (left == 0) {
		return pos == targetpos;
	}
	if (pos.first == pos.second && board[pos.first.first][pos.first.second] == 'c')
		toggleState = !toggleState;
	int DX[4] = {-1, 1, 0, 0}, DY[4] = {0,0,1,-1};
	for (int d = 0; d < 4; d++) {
		int dx = DX[d], dy = DY[d];
		pair<pii, pii> pos2 = pos;
		pos2.first.first += dy;
		pos2.second.first += dy;
		pos2.first.second += dx;
		pos2.second.second += dx;
		if (pos.first == pos.second) {
			pos2.first.first += dy;
			pos2.first.second += dx;
		}
		else if ((dx != 0) == (pos.first.second != pos.second.second)) {
			if (pos2.first == pos.first || pos2.first == pos.second)
				pos2.first = pos2.second;
			else
				pos2.second = pos2.first;
		}
		if (oob(pos2.first, toggleState) || oob(pos2.second, toggleState))
			continue;
		if (dfs(pos2, left-1, toggleState))
			return true;
	}
	return false;
}

int main() {
	cin.sync_with_stdio(false);
	cin >> H >> W;
	board.resize(H);
	rep(i,0,H) cin >> board[i];
	int startx = -1, starty = -1, endx = -1, endy = -1;
	rep(i,0,H) rep(j,0,W) if (board[i][j] == 'A') {
		starty = i, startx = j;
		board[i][j] = '.';
	} else if (board[i][j] == 'B') {
		endy = i, endx = j;
		board[i][j] = '.';
	}
	pii t(endy, endx);
	targetpos = make_pair(t,t);
	for (int d = 1;; d++) {
		pii s(starty, startx);
		pair<pii, pii> pos(s,s);
		if (dfs(pos, d, false)) {
			cout << d << endl;
			return 0;
		}
	}
}
