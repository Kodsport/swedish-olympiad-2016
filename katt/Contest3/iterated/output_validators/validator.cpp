// usage: ./a.out input_file correct_output output_dir < contestants_output

#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < int(to); ++i)
#define sz(x) (int)(x).size()

string output_dir, type;

void die(const string& msg) {
	cout << msg << endl;
	ofstream(output_dir + "/score.txt") << 0;
    exit(43);
}

void accept(double score, int real_score) {
	ofstream(output_dir + "/score.txt") << fixed << setprecision(2) << score;
	ofstream(output_dir + "/judgemessage.txt") << real_score;
    exit(42);
}

void safe_print(int n) {
	try {
		cout << n << endl;
	} catch(...) {}
}

int N;
double score(int guesses, int best) {
	if (type == "exp") {
		assert(N <= 30);
		return (guesses <= (1 << N));
	}
	if (type == "2n") return (guesses <= 2*N);
	if (type == "n") return (guesses <= 2+N);
	if (type == "rel") {
		if (guesses >= N) return 0;
        assert(guesses >= best);
		int a = N - guesses, b = N - best;
		return a / (double)b;
	}
	assert(false);
}

int main(int argc, char** argv) {
	if (argc < 3) exit(1);
	cin.sync_with_stdio(0);
	cin.tie(0);
	int max_score, seed;
	ifstream(argv[1]) >> N >> type >> max_score >> seed;
	output_dir = argv[2];
	srand(seed);

	string guess, target(N, '0');
	rep(i,0,N) target[i] = (char)('0' + ((rand() >> 24) & 1));

	safe_print(N);
	int guesses = 0;
	while (guess != target) {
        guesses++;
		try {
			getline(cin, guess);
			if (!cin) throw 0;
		} catch(...) {
			die("no input!");
		}
		if (sz(guess) != N)
            die("wrong length");
        int s = 0;
		rep(i,0,N) {
			char x = guess[i];
            if (x != 48 && x != 49)
                die("invalid char in guess");
			if (x == target[i])
				s++;
		}
        safe_print(s);
	}
    double sc = score(guesses, N / 2);
    if (sc == 0)
        die("too many guesses");
    accept(max_score * sc, guesses);
}
