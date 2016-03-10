#include <iostream>
using namespace std;

typedef long long ll;

int main() {
	int N, H;
	cin >> N >> H;
	int x0 = -1, y0 = -1;
	int x1 = -1, y1 = -1;
	for (int i = 0; i < N; i++) {
		int x2, y2, z;
		cin >> x2 >> y2 >> z;
		if (x0 != -1) {
			// (y0 - y1) / (x0 - x1) >= (y1 - y2) / (x1 - x2)
			// (y0 - y1) * (x1 - x2) >= (y1 - y2) * (x0 - x1)
			ll A = (y0 - y1) * (ll)(x1 - x2);
			ll B = (y1 - y2) * (ll)(x0 - x1);
			if (A < B)
				return 1;
		}
		x0 = x1; y0 = y1;
		x1 = x2; y1 = y2;
	}
	return 0;
}
