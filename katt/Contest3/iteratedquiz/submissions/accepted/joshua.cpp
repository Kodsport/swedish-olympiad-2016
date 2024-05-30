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

#define LDEBUG 0
#if !LDEBUG
int ask(vi& q)
{
	rep(i, sz(q)) cout << (q[i] ? '1' : '0');
	cout << endl;
	int resp;
	cin >> resp;
	return resp;
}
#else
vi secr;
int ask(vi& q)
{
	if (secr.empty()) rep(i, 1000) secr.push_back(rand() % 2);
	int res = 0;
	rep(i, 1000)
	{
		res += secr[i] == q[i];
	}

	return res;
}
#endif

int find_query(vi& candidates, int n)
{
	double d = 0.5;
	uniform_real_distribution<float> dist(0, 1);
	mt19937 rng(5);

	vi classes(n * 2 + 2);
	int smallest = inf;
	int bestmask = -1;
	int its = candidates.size() < 250 ? 4000 : 500;
	rep(i, its)
	{
		int q = 0;
		rep(j, n) if (dist(rng) > d) q |= 1 << (j);
		int cost = 0;
		rep(i, sz(classes)) classes[i] = 0;

		repe(c, candidates)
		{
			int v = popcnt(c);
			int k = n - popcnt(c ^ q);
			classes[v - k + n]++;
		}
		repe(c, classes) cost += c * c;
		if (cost < smallest)
		{
			smallest = cost;
			bestmask = q;
		}
	}
	return bestmask;
}

signed main()
{
	fast();

	int n;
#if LDEBUG
	n = 1000;
#else
	cin >> n;
#endif
	if (n < 1000)
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
	else
	{
		vi base(n, 1);
		int baseline = ask(base);
		const int blocksize = 23;
		const int rounds = 43;
		assert(rounds * blocksize <= 1000);
		vi queries = { 1081601, 2432052, 6906410, 4861508, 973026, 2355293, 6230551, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

		vi ans(n);
		const int brute_cutoff = 4000;
		auto do_round = [&ans, n, &queries, baseline, brute_cutoff](vi& candidates, int offset, int blocksize)
		{
			vi q(n, 1);
			repe(qu, queries)
			{
				if (sz(candidates) < brute_cutoff)
				{
					qu = find_query(candidates, blocksize);
				}
				rep(j, blocksize)
				{
					if (qu & (1 << j)) q[offset + j] = 1;
					else q[offset + j] = 0;
				}
				int res = ask(q);
				int delta = res - baseline;
				vi newcandidates;

				repe(c, candidates)
				{
					int bc = popcnt(c);
					int k = blocksize - popcnt(c ^ qu);
					if (bc - k == delta)
					{
						newcandidates.push_back(c);
					}
				}
				candidates = newcandidates;
				if (sz(candidates) == 1)
				{
					break;
				}
			}
			rep(j, blocksize)
			{
				ans[offset + j] = (candidates[0] & (1 << j)) == 0;
			}
		};

		
		rep(i, rounds)
		{
			vi candidates(1 << blocksize);
			rep(i, 1 << blocksize) candidates[i] = i;
			do_round(candidates, i * blocksize, blocksize);
		}

		// find the last n%blocksize bits
		int remainder = n % blocksize;
		assert((1 << remainder) < brute_cutoff);
		vi candidates(1 << remainder);
		rep(i, 1 << remainder) candidates[i] = i;
		do_round(candidates, rounds* blocksize, remainder);
		

#if LDEBUG
		assert(ans == secr);
#endif
		ask(ans);
	}
	return 0;

}
