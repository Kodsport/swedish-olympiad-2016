// usage: ./a.out input_file correct_output output_dir < contestants_output

#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < int(to); ++i)
#define sz(x) (int)(x).size()
typedef vector<int> vi;

string output_dir;

void die(const string& msg) {
	cout << msg << endl;
	ofstream(output_dir + "/score.txt") << 0;
    exit(43);
}

void accept(int score) {
	ofstream(output_dir + "/score.txt") << score;
    exit(42);
}

void assert_done(istream& is) {
	try {
		string dummy;
		is >> dummy;
		die("extraneous data: " + dummy);
	} catch(...) {}
}

int main(int argc, char** argv) {
	if (argc < 4) exit(1);
	cin.sync_with_stdio(0);
	cin.tie(0);

	int max_score = /* I dunno */ 20;
	assert(max_score % 4 == 0);

	output_dir = argv[3];

	ifstream fin(argv[1]);
	fin.exceptions(cin.failbit | cin.badbit | cin.eofbit);
	int N, K;
	fin >> N >> K;
	vi L(N), R(N);
	rep(i,0,N) fin >> L[i];
	rep(i,0,N) fin >> R[i];
	assert_done(fin);
	fin.close();

	int answer;
	fin.open(argv[2]);
	fin >> answer;

	int output;
	cin >> output;
	if (output != answer)
		die("invalid answer");
	vi trick(N);
	rep(i,0,N)
		cin >> trick[i];
	assert_done(cin);

	bool fail = false;
	{
	int moves = 0;
	long long score = 0;
	rep(i,0,N) {
		int x = trick[i];
		if (x < -K || K < x)
			fail = true; // too many rabbits at once
		else {
			moves += abs(x);
			if (moves > K)
				fail = true; // too many rabbits in total
			else {
				int mid = (L[i] + R[i]) / 2;
				if (L[i] <= x && x <= R[i])
					score += abs(x - mid);
			}
		}
	}
	if (score != output)
		fail = true; // incorrect reconstruction
	}

	int score = max_score;
	if (fail)
		score = score * 3 / 4;
	accept(score);
}
