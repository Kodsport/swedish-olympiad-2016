#include <bits/stdc++.h>
using namespace std;

int main() {
	string pat = "UUNNVHVHBA", inp;
	cin >> inp;
	int N = (int)inp.size(), res = 1 << 29;
	array<int, 128> cur{};
	vector<array<int, 128> > nexts(N);
	for (int i = N; i --> 0;) {
		cur[inp[i]] = i+1;
		nexts[i] = cur;
	}
	for (int i = 0; i < N; ++i) {
		int at = i;
		for (int j = 0; j < (int)pat.size(); ++j) {
			at = nexts[at][pat[j]];
			if (at == 0) goto fail;
		}
		res = min(res, at - i - (int)pat.size());
fail:;
	}
	cout << res << endl;
}
