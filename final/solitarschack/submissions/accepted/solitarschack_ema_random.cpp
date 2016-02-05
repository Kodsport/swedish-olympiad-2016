#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < int(b); i++)
#define trav(it, v) for(auto it = v.begin(); it != v.end(); it++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x).size()
 
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi; 
 
struct Piece {
	int t, v, r, c;

	void setType(string type) {
		if (type.size() == 1) {
			t = type[0] - '0';
		} else if (type == "torn") {
			t = 5;
		} else if (type == "lopare") {
			t = 6;
		} else if (type == "dam") {
			t = 7;
		} else if (type == "springare") {
			t = 8;
		} else {
			t = 0;
		}
	}

	Piece(int t, int v, int r, int c): t(t), v(v), r(r), c(c) {}
	Piece(string type, int v, int r, int c): v(v), r(r), c(c) {
		setType(type);
	}
};

bool canMove(Piece& a, Piece& b, int type) {
	if (b.t == 0) return false;
	if (type < 5) {
		return ((abs(a.r - b.r) == type && abs(a.c - b.c) == 0) ||
		    (abs(a.r - b.r) == 0 && abs(a.c - b.c) == type) ||
		    (abs(a.r - b.r) == type && abs(a.c - b.c) == type));
	} else if (type == 5) {
		return (a.r == b.r && (b.c == 0 || b.c == 5)) || 
		       (a.c == b.c && (b.r == 0 || b.r == 5));
	} else if (type == 6) {
		return (abs(a.r - b.r) == abs(a.c - b.c)) && (b.r == 0 || b.r == 5 || b.c == 0 || b.c == 5);
	} else if (type == 7) {
		return (a.r == b.r && (b.c == 0 || b.c == 5)) || 
		       (a.c == b.c && (b.r == 0 || b.r == 5)) ||
		       ((abs(a.r - b.r) == abs(a.c - b.c)) && (b.r == 0 || b.r == 5 || b.c == 0 || b.c == 5));
	} else if (type == 8) {
	        return (abs(a.r - b.r) == 1 && abs(a.c - b.c) == 2) ||
		       (abs(a.r - b.r) == 2 && abs(a.c - b.c) == 1);	
	}
	return false;
}

void read(vector<Piece>& p) {
	rep(r, 0, 6) {
		rep(c, 0, 6) {
			int v = 1;
			string type;
			cin >> type;
			p.push_back(Piece(type, v, r, c));
		}
	}
}

void makeMove(vector<Piece>& p, int i) {
	cout << p[i].r+1 << " " << p[i].c+1 << endl;
	flush(cout);
	string type;
	cin >> type;
	p[i].setType(type);
	p[i].v++;
}

int main() {
	vector<Piece> p;
	read(p);
	srand(time(NULL));
	int i = rand()%(p.size());
	int lastType = p[i].t;
	makeMove(p, i);
	while(true) {
		vector<int> options;
		rep(j, 0, p.size()) {
			if (p[j].v < 4 && canMove(p[i], p[j], lastType)) {
				options.push_back(j);
			}
		}
		if (options.empty()) break;
		i = options[rand()%options.size()];
		lastType = p[i].t;
		makeMove(p, i);
	}
	cout << "0 0" << endl;
	return 0;
}
