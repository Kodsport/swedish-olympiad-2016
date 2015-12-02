#include <iostream>
#include <vector>

using namespace std;

/** TODO: Generates test cases upside down */
int main () {
	int n, k;
	cin >> n >> k;

	vector<int> xs(n);
	vector<int> ys(n);
	for (int i = 0; i < n; i++) {
		cin >> xs[i] >> ys[i];
	}

	int max_x = xs[0];
	int min_x = xs[0];
	int max_y = ys[0];
	int min_y = ys[0];
	for (int i = 0; i < n; i++) {
		max_x = max(max_x, xs[i]);
		min_x = min(min_x, xs[i]);
		max_y = max(max_y, ys[i]);
		min_y = min(min_y, ys[i]);
	}

	if (max_x - min_x > 8000) return 1;
	if (max_y - min_y > 8000) return 1;

	max_x++;
	max_y++;

	vector<vector<bool> > dots (max_x-min_x, vector<bool>(max_y-min_y));
	for (int i = 0; i < n; i++) {
		dots[xs[i]-min_x][ys[i]-min_y] = true;
	}

	cout << "P1" << endl;
	cout << (max_x - min_x) << " " << (max_y - min_y) << endl;
	for (int y = max_y - min_y - 1; y >= 0; y--) {
		for (int x = 0; x < max_x - min_x; x++) {
			cout << dots[x][y] << " ";
		}
		cout << endl;
	}

}
