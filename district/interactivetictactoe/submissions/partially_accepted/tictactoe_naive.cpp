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

typedef array<int, 9> Board;

int conv(char c) {
	if (c == 'o') return -1;
	if (c == '.') return 0;
	if (c == 'x') return 1;
	assert(0);
}

char conv(int c) {
	if (c == -1) return 'o';
	if (c == 0) return '.';
	if (c == 1) return 'x';
	assert(0);
}

bool full(Board b) {
	trav(x, b) if (x == 0) return false;
	return true;
}
int winner(Board b) {
#define TEST(a, b, c) if (a == b && b == c && c != 0) return c
	rep(i,0,3) {
		TEST(b[i*3+0], b[i*3+1], b[i*3+2]);
		TEST(b[i+0], b[i+3], b[i+6]);
	}
	TEST(b[0], b[4], b[8]);
	TEST(b[2], b[4], b[6]);
	return 0;
#undef TEST
}
bool done(Board b) { return full(b) || winner(b) != 0; }

// Play naively
int play(Board b) {
	rep(i,0,9) {
		if (b[i] == 0) return i;
	}
	assert(0);
}

int main() {
	cin.sync_with_stdio(false);
	cin.exceptions(cin.badbit | cin.failbit);
	string line;
	getline(cin, line);
	Board prevBoard{};
	bool first = (line == "first");
	for (;;) {
		Board board;
		rep(i,0,3) {
			getline(cin, line);
			rep(j,0,3) board[i*3+j] = conv(line[j]);
		}
		int diffs = 0;
		rep(i,0,9) {
			if (board[i] != prevBoard[i]) {
				assert(prevBoard[i] == 0);
				diffs++;
			}
		}
		assert(diffs == (first ? 0 : 1));
		first = false;
		if (done(board)) return 0;
		Board b2 = board;
		b2[play(board)] = 1;
		prevBoard = b2;
		rep(i,0,3) {
			rep(j,0,3) {
				cout << conv(b2[i*3+j]);
			}
			cout << '\n';
		}
		flush(cout);
		if (done(b2)) return 0;
	}
}
