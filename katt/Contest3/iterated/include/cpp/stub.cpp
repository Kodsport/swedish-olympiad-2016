#include "iterated.h"
#include <bits/stdc++.h>
using namespace std;

ifstream fin;
ofstream fout;

static int N;
int guess(const int ans[]) {
	string guess;
	guess.reserve(N);
	for (int i = 0; i < N; i++)
		guess += ans[i] ? '1' : '0';
	fout << guess << endl;
	int res;
	fin >> res;
	if (res == N)
		exit(0);
	return res;
}

int main(int argc, char** argv) {
  fin.open(argv[1], ifstream::in|ifstream::out);
  fout.open(argv[2], ofstream::out|ofstream::in);
  fin >> N;
	init(N);
}
