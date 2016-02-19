// Generates a test case with a random tree of N nodes
// params: N K seed

#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < int(b); i++)
#define trav(it, v) for(auto it = v.begin(); it != v.end(); it++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x).size()

void treeDfs(int i, vector<vector<int> >& adj, vector<int>& par) {
	trav(it, adj[i]) {
		if (*it != par[i]) {
			par[*it] = i;
			treeDfs(*it, adj, par);
		}
	}
}

int main(int argc, char* argv[]) {
	if (argc < 4) {
		cerr << "Error: not enough arguments";
		return 0;
	}
	int N = atoi(argv[1]);
	int K = atoi(argv[2]);
	int seed = atoi(argv[3]);
	srand(seed);
	vector<int> prufer(N-2), degree(N+1, 1);
	rep(i, 0, N-2) {
		prufer[i] = (rand()%N) + 1; 
		degree[prufer[i]]++;
	}
	vector<vector<int> > adj(N+1, vector<int>());
	set<int> nextNode;
	rep(i, 1, N+1) {
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
	rep(i, 1, N+1) {
		if (degree[i] == 1) {
			if (a != -1) b = i;
			else a = i;
		}
	}
	adj[a].push_back(b);
	adj[b].push_back(a);
	
	int root = (rand()%N) + 1;
	vector<int> par(N+1, 0);
	treeDfs(root, adj, par);
	
	cout << N << " " << K << endl;
	bool first = true;
	rep(i, 1, N+1) {
		if (par[i] == 0) continue;
		if (!first) cout << " ";
		first = false;
		cout << par[i]-1;
	}
	cout << endl;
	first = true;
	rep(i, 1, N+1) {
		if (par[i] == 0) continue;
		if (!first) cout << " ";
		first = false;
		cout << i-1;
	}
	cout << endl;
}
