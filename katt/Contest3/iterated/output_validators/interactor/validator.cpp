// usage: ./a.out input_file correct_output output_dir < contestants_output

#include <bits/stdc++.h>
#include "validate.h"
using namespace std;

#define rep(i, from, to) for (int i = from; i < int(to); ++i)
#define sz(x) (int)(x).size()

string type;

int N;
double score(int guesses) {
	if (type == "exp") {
		assert(N <= 30);
		return (guesses <= (1 << N));
	}
	if (type == "2n") return (guesses <= 2*N);
	if (type == "n") return (guesses <= 2+N);
	if (type == "rel") {
		if (guesses >= N) return 0;
		return min(1.0, (1000.0-guesses)/(1000-420));
	}
	assert(false);
}

void wa(string message)
{
	wrong_answer(message.c_str());
}

int main(int argc, char** argv) {
	init_io(argc, argv);

	int max_score, seed;
    judge_in >> N >> type >> max_score >> seed;

	srand(seed);

	string guess, target(N, '0');
	rep(i,0,N) target[i] = (char)('0' + ((rand() >> 24) & 1));

	cout << N << endl;
	int guesses = 0;
	while (guess != target) {
        guesses++;
		if (!(cin >> guess)) wa("Expected more output");

		if (sz(guess) != N)
			wa(("wrong length"+to_string(sz(guess))+" "+guess+" "+to_string(N)));
		int s = 0;
		rep(i,0,N) {
			char x = guess[i];
			if (x != 48 && x != 49)
				wa("invalid char in guess");
			if (x == target[i])
				s++;
		}
		cout << s << endl;		
	}
    double sc = score(guesses);
    //if (type=="rel") accept_with_score(1000-guesses);
	accept_with_score(max_score * sc);
}
