// Generates a test case with a random tree of N nodes
// params: N K seed

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); i++)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x).size()
typedef vector<int> vi;
typedef long long ll;
typedef pair<int, int> pii;

bool NO, POS, TWO;

vector<pii> eds;

void prv(vi& v) {
	bool first = true;
	trav(x, v) {
		if (first) first = false;
		else cout.put(' ');
		cout << x;
	}
	cout << endl;
}

void treeDfs(int i, vector<vi>& adj, vi& par) {
	trav(j, adj[i]) {
		if (j == par[i]) continue;
		eds.emplace_back(i, j);
		par[j] = i;
		treeDfs(j, adj, par);
	}
}

vector<vi> comps;
void dfs(int i, vector<vi>& adj, vi& par, vi& stop, vi& upComp) {
	vi newComp;
	vi& comp = stop[i] ? newComp : upComp;
	comp.push_back(i);
	trav(j, adj[i]) {
		if (j == par[i]) continue;
		dfs(j, adj, par, stop, comp);
	}
	if (stop[i]) comps.push_back(newComp);
}

vi X;
ll each;
void assign(vi& comp, ll sum) {
	ll cur = 0;
	assert(!comp.empty());
	rep(i,0,sz(comp)-1) {
		int v = (int)(rand() % (each * 2 + 1) - each);
		if (POS) v = rand() % 2 + 1;
		X[comp[i]] = v;
		cur += v;
	}
	X[comp.back()] = (int)(sum - cur);
}

int main(int argc, char* argv[]) {
	if (argc < 6) {
		cerr << "Error: not enough arguments" << endl;
		return 0;
	}
	int N = atoi(argv[1]);
	int K = atoi(argv[2]);
	each = atoi(argv[3]);
	string cas = argv[4];
	NO = cas.find("no") != string::npos;
	POS = cas.find("pos") != string::npos;
	TWO = cas.find("two") != string::npos;
	int seed = atoi(argv[5]);
	srand(seed);
	vi prufer(N-2), degree(N, 1);
	rep(i, 0, N-2) {
		prufer[i] = (rand()%N);
		degree[prufer[i]]++;
	}
	vector<vi> adj(N, vi());
	set<int> nextNode;
	rep(i, 0, N) {
		if (degree[i] == 1) nextNode.insert(i);
	}
	rep(i, 0, N-2) {
		int a = prufer[i];
		int b = *nextNode.begin();
		nextNode.erase(nextNode.begin());
		degree[a]--;
		degree[b]--;
		if (degree[a] == 1) nextNode.insert(a);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	int a = -1, b = -1;
	rep(i, 0, N) {
		if (degree[i] == 1) {
			if (a != -1) b = i;
			else a = i;
		}
	}
	adj[a].push_back(b);
	adj[b].push_back(a);

	int root = (rand()%N);
	vi par(N, -1);
	treeDfs(root, adj, par);

	vi stop(N);
	assert(0 < K && K <= N);
	rep(i,0,K-1) stop[i] = 1;
	do random_shuffle(all(stop));
	while (stop[root]);
	stop[root] = 1;

	vi _;
	dfs(root, adj, par, stop, _);

	int res = 0;
	do {
		int distr[] = {1, 1, 1, 1, 0, 0, -1, -2};
		if (POS) distr[4] = distr[5] = distr[6] = distr[7] = 1;
		if (NO) distr[0] = 2;
		if (NO && !POS) distr[1] = 2;
		res = 0;
		X.assign(N, -123456);
		trav(c, comps) {
			int t = distr[rand() % (sizeof distr / sizeof *distr)];
			if (TWO) t = 1;
			assign(c, t * each);
			res += t;
		}
		trav(x, X) assert(x != -123456);
	} while (res <= 0);

	if (TWO && NO) res = 2;
	if (TWO && !NO) assert(res == 2);

	random_shuffle(all(eds));
	int ind = 0;
	vi F(N-1), T(N-1);
	trav(e, eds) {
		if (rand() & 32) swap(e.first, e.second);
		F[ind] = e.first;
		T[ind] = e.second;
		ind++;
	}
	assert(ind == N-1);

	if (POS) {
		trav(x, X) assert(x > 0);
	}

	int P = res;
	cout << N << ' ' << P << endl;
	prv(X);
	prv(F);
	prv(T);
}
