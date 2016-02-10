#include "mastermind.h"
#include <bits/stdc++.h>
using namespace std;

static string target;
static int N, guesses = 0;
int guess(const bool ans[]) {
	guesses++;
	int same = 0;
	for (int i = 0; i < N; i++) {
		char c = target[i], d = ans[i] ? '1' : '0';
		same += (c == d);
	}
	if (same == N) {
		cout << "Success, took " << guesses << " guesses." << endl;
		exit(0);
	}
	return same;
}

int main() {
	cin.sync_with_stdio(false);
	cin >> target;
	N = (int)target.size();
	for (int i = 0; i < N; i++) {
		if (target[i] != '0' && target[i] != '1')
			cerr << "Invalid input string." << endl, exit(2);
	}
	init(N);
	cout << "Failure." << endl;
	exit(1);
}
