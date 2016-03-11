#include <bits/stdc++.h>
#include "kingdom.h"
using namespace std;

#define rep(i, from, to) for (int i = from; i < int(to); ++i)
#define trav(a, x) for (auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

int partsleft;
ll D;

struct Node {
	vector<Node*> ch;
	int value;
	void root(Node* par);
	ll solve();
};

void Node::root(Node* par) {
	ch.erase(remove(all(ch), par), ch.end());
	trav(x, ch)
		x->root(this);
}

ll Node::solve() {
	ll w = 0;
	trav(x, ch)
		w += x->solve();
	w += value;
  if (w == D) {
    partsleft--;
    return 0;
  }
	return w;
}

int division(int N, int P, int C[], int F[], int T[]) {
	ll tot = 0;
	rep(i,0,N) tot += C[i];
	if (tot % P != 0) return 0;
	D = tot / P;
	partsleft = P - 1;
	vector<Node> nodes(N);
	rep(i,0,N)
		nodes[i].value = C[i];
	rep(i,0,N-1) {
		nodes[F[i]].ch.push_back(&nodes[T[i]]);
		nodes[T[i]].ch.push_back(&nodes[F[i]]);
	}
	Node* root = &nodes[0];
	root->root(0);
	root->solve();
	if (partsleft > 0) return 0;
	return 1;
}
