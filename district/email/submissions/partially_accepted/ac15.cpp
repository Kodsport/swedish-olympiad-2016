#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < int(to); ++i)
#define trav(a, x) for (auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

void read(string& line) {
	getline(cin, line);
	if (!line.empty() && line[line.size()-1] == '\r')
		line.erase(line.end()-1);
}

int main() {
	cin.sync_with_stdio(false);
	string str, term;
	do read(str); while (!str.empty());
	read(term);
	term += "--";
	do read(str); while (!str.empty());
	for (;;) {
		read(str);
		if (str == term) break;
		cout << str << endl;
	}
}
