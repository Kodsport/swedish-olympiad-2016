#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)
#define ceildiv(x,y) ((x + y - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }

#if _LOCAL
#define __builtin_popcount popcount
#define assert(x) if (!(x)) __debugbreak()
#endif

int popcnt(int x) { return __builtin_popcount((unsigned long long)x); }

int ask(vi& q)
{
	rep(i, sz(q)) cout << (q[i] ? '1' : '0');
	cout << endl;
	int resp;
	cin >> resp;
	return resp;
}


signed main()
{
	fast();

	int n;
	cin >> n;

	if (n <= 1000)
	{
		vi ans(n);
		vi q(n);
		int baseline = ask(q);
		rep(i, n)
		{
			if (i) q[i - 1] = 0;
			q[i] = 1;
			if (ask(q) > baseline) ans[i] = 1;
		}
		ask(ans);
	}
	
	return 0;
}
