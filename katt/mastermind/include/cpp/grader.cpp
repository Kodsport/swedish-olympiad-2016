#include "mastermind.h"
#include <bits/stdc++.h>
using namespace std;

static int N;
int guess(const bool ans[]) {
	string guess;
	guess.reserve(N);
	for (int i = 0; i < N; i++)
		guess += ans[i] ? '1' : '0';
	cout << guess << endl;
	int res;
	cin >> res;
	if (res == N)
		exit(0);
	return res;
}

int main() {
	cin.sync_with_stdio(false);
	cin >> N;
	init(N);
}
