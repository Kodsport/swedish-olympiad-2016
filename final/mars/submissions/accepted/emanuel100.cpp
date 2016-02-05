#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < int(b); i++)
#define trav(it, v) for(auto it = v.begin(); it != v.end(); it++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x).size()
 
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi; 
 
int main() {
	int N;
	cin >> N;
	rep(i, 0, N/2) {
		double a, b;
		cin >> a >> b;
		int A = (int)(a/22.5);
		int B = (int)(b/22.5);
		cout << (char)(16*A + B);
	}
	cout << endl;
}

