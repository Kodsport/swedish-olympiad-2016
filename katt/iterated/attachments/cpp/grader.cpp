#include "iterated.h"
#include <bits/stdc++.h>
using namespace std;

static string target;
static int N, guesses = 0;
int guess(const int ans[]) {
	guesses++;
	int same = 0;
	for (int i = 0; i < N; i++) {
		char c = target[i], d = ans[i] ? '1' : '0';
		same += (c == d);
	}
	if (same == N) {
		cout << guesses << endl;
		exit(0);
	}
	return same;
}

int main() {
	cin.sync_with_stdio(false);
  cin >> N;
	cin >> target;
  if (int(target.size()) != N) {
    cerr << "Invalid input string." << endl;
    exit(2);
  }
	for (int i = 0; i < N; i++) {
		if (target[i] != '0' && target[i] != '1')
			cerr << "Invalid input string." << endl, exit(2);
	}
	init(N);
	cout << "Failure." << endl;
	exit(1);
}
