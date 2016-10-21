// usage: ./a.out input_file correct_output contestant < contestants_output

#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < int(to); ++i)
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
typedef vector<int> vi;

string input_file, contestant, answer_file;

void die(const string& msg) {
  cout << 0.0 << endl;
  cout << msg << endl;
	exit(0);
}

void accept(double score) {
  cout << score << endl;
	exit(0);
}

void assert_done(istream& is) {
	try {
		string dummy;
		is >> dummy;
		die("extraneous data: " + dummy);
	} catch(...) {}
}

bool is_twocolorable(int N, int M, vector<int>& A, vector<int>& B, vector<int>& C, vector<bool>& included) {
  vector<vector<pair<int, int>>> edges(N);
  rep(i,0,M) if (included[i]) {
    edges[A[i]].emplace_back(B[i], 1-C[i]);
    edges[B[i]].emplace_back(A[i], 1-C[i]);
  }
  vector<int> color(N, -1);
  color[0] = 0;
  queue<int> q;
  q.push(0);
  while (!q.empty()) {
    int nx = q.front();
    q.pop();
    for(auto& it : edges[nx]) {
      int v = it.first;
      int d = it.second;
      if (color[v] >= 0){
        if ((color[v] ^ d) != color[nx]) return false;
      } else {
        color[v] = color[nx] ^ d;
        q.push(v);
      }
    }
  }
  return true;
}

int main(int argc, char** argv) {

	input_file = argv[1];
	contestant = argv[3];

	ifstream fin(input_file);
	fin.exceptions(cin.failbit | cin.badbit | cin.eofbit);
	int N, M, C;
	fin >> N >> M;
  fin >> C;
	vi A(M), B(M), T(M);
	rep(i,0,M) fin >> A[i];
	rep(i,0,M) fin >> B[i];
	rep(i,0,M) fin >> T[i];
	assert_done(fin);
	fin.close();

  vector<bool> included(M);
  fin.open(contestant);
	try {
		fin.exceptions(cin.failbit | cin.badbit | cin.eofbit);
    int ans = 0;
    rep(i,0,M) {
      int output;
      fin >> output;
      if (output != 0 && output != 1) die("invalid answer");
      if (output) included[i] = true;
      ans += output;
    }
		assert_done(fin);

    if (!is_twocolorable(N, M, A, B, T, included)) {
      die("set is not consistent");
    }

    double q1 = (double)ans / N - 0.5;
    double q2 = (double)C / N - 0.5;

		accept( max(0.0,  q1 / q2) );
	} catch(...) {
		die("IO failure");
	}
}
