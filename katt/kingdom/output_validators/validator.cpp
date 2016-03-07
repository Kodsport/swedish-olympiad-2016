// usage: ./a.out input_file correct_output output_dir < contestants_output

#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < int(to); ++i)
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
typedef vector<int> vi;

string input_file, output_dir, answer_file;

void die(const string& msg) {
	cout << msg << endl;
	ofstream(output_dir + "/score.txt") << 0;
	exit(43);
}

void accept(double score) {
	ofstream(output_dir + "/score.txt") << setprecision(2) << fixed << score;
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

	input_file = argv[1];
	answer_file = argv[2];
	output_dir = argv[3];

	ifstream fin(input_file);
	fin.exceptions(cin.failbit | cin.badbit | cin.eofbit);
	int N, P;
	fin >> N >> P;
	vi C(N), F(N - 1), T(N - 1);
	rep(i,0,N - 1) fin >> F[i];
	rep(i,0,N - 1) fin >> T[i];
	assert_done(fin);
	fin.close();

	int answer;
	fin.open(answer_file);
	fin >> answer;

	try {
		cin.exceptions(cin.failbit | cin.badbit | cin.eofbit);
		int output;
		cin >> output;
		if (output != answer)
			die("invalid answer");
		vi part(N);
		rep(i,0,N)
			cin >> part[i];
		assert_done(cin);

		int fail = 0;
		{
			for (int i = 0; i < N; ++i) {
				if (part[i] < 0 || part[i] >= P) {
					fail = 1; // invalid part
					goto done;
				}
			}
			int same = 0;
			for (int i = 0; i < N - 1; ++i) {
				if (part[F[i]] == part[T[i]]) same++;
			}
			if (same != N - P) { 
				fail = 2; // not connected
				goto done;
			}
			long long target = accumulate(all(C), 0LL) / P;
			vector<long long> scores(P);
			for (int i = 0; i < N; ++i) {
				scores[part[i]] += C[i];
			}
			for (int i = 0; i < P; ++i) {
				if (target != scores[i]) {
					fail = 3; // bad scores
					goto done;
				}
			}
		}
done: 
		accept(fail ? 0.75 : 1.00);
	} catch(...) {
		die("IO failure");
	}
}
