// usage: ./a.out input_file correct_output output_dir < contestants_output

#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < int(to); ++i)
#define sz(x) (int)(x).size()
typedef vector<int> vi;

string input_file, contestant, answer_file;

void die(const string& msg) {
	cout << 0.0 << endl;
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

int main(int argc, char** argv) {

	input_file = argv[1];
	answer_file = argv[2];
	contestant = argv[3];

	ifstream fin(input_file);
	fin.exceptions(cin.failbit | cin.badbit | cin.eofbit);
	int N, K;
	fin >> N >> K;
	vi L(N), R(N);
	rep(i,0,N) fin >> L[i];
	rep(i,0,N) fin >> R[i];
	assert_done(fin);
	fin.close();

	int answer;
	fin.open(answer_file);
	fin >> answer;
	fin.close();

	fin.open(contestant);

	try {
	fin.exceptions(cin.failbit | cin.badbit | cin.eofbit);
	int output;
	fin >> output;
	if (output != answer)
		die("invalid answer");
	vi trick(N);
	rep(i,0,N)
		fin >> trick[i];
	assert_done(fin);

	int fail = 0;
	{
	int moves = 0;
	long long score = 0;
	rep(i,0,N) {
		int x = trick[i];
		if (x < -K || K < x)
			fail = 1; // too many rabbits at once
		else {
			moves += abs(x);
			if (moves > K)
				fail = 2; // too many rabbits in total
			else {
				int mid = (L[i] + R[i]) / 2;
				if (L[i] <= x && x <= R[i])
					score += abs(x - mid);
			}
		}
	}
	if (score != output && !fail)
		fail = 3; // incorrect reconstruction
	}

	accept(fail ? 0.75 : 1.00);
	} catch(...) {
		die("IO failure");
	}
}
