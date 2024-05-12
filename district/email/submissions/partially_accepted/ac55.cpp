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

bool startswith(const string& a, const string& b) {
	return a.substr(0, b.size()) == b;
}

int fromhex(char c) {
	if ('A' <= c && c <= 'F') return c - 'A' + 10;
	if ('a' <= c && c <= 'f') return c - 'a' + 10;
	if ('0' <= c && c <= '9') return c - '0';
	assert(0);
}

int main() {
	cin.sync_with_stdio(false);
	string str, term;
	string boundary;
	for (;;) {
		read(str);
		if (str.empty()) break;
		if (startswith(str, "Content-Type:")) {
			str = str.substr(string("Content-Type:").size());
			size_t ind = str.find("boundary=");
			if (ind == string::npos) continue;
			str = str.substr(ind + 9);
			if (str[0] == '"') {
				str = str.substr(1);
				ind = str.find('"', 1);
			}
			else {
				ind = str.find(';');
				if (ind == string::npos) ind = str.size();
			}
			boundary = str.substr(0, ind);
		}
	}
	assert(!boundary.empty());
	boundary = "--" + boundary;
	vector<string> v;
	for (;;) {
		read(str);
		if (startswith(str, boundary)) {
			if (str != boundary) {
				v.pop_back();
				break;
			}
			v.clear();
		}
		else v.push_back(str);
	}
	int i = 0;
	string conttype, contenc = "7bit";
	while (!v[i].empty()) {
		str = v[i];
		if (startswith(str, "Content-Transfer-Encoding: ")) {
			str = str.substr(string("Content-Transfer-Encoding: ").size());
			str = str.substr(0, str.find(';'));
			contenc = str;
		}
		if (startswith(str, "Content-Type: ")) {
			str = str.substr(string("Content-Type: ").size());
			str = str.substr(0, str.find(';'));
			conttype = str;
		}
		++i;
	}
	++i;
	string data;
	if (contenc == "7bit") {
		while (i < sz(v)) {
			data += v[i];
			data += '\n';
			++i;
		}
	} else {
		assert(contenc == "quoted-printable");
		while (i < sz(v)) {
			string& s = v[i];
			bool nl = true;
			if (!s.empty() && s[s.size()-1] == '=') {
				s = s.substr(0, s.size()-1);
				nl = false;
			}
			string s2;
			for (int j = 0; j < sz(s); ++j) {
				if (s[j] == '=') {
					int a = fromhex(s[++j]), b = fromhex(s[++j]);
					s2 += (char)(a * 16 + b);
				}
				else s2 += s[j];
			}
			data += s2;
			if (nl)
				data += '\n';
			++i;
		}
	}
	cout << data;
}
