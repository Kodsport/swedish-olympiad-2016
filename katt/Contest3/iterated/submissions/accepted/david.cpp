#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <set>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <bitset>
#include <random>
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace std;
#define rep(i,a,b) for(int i = (a); i < int(b); ++i)
#define rrep(i,a,b) for(int i = (b); i --> int(a);)
#define allof(v) v.begin(),v.end()
#define pb push_back
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int,int> pii;
typedef vector<bool> vb;
typedef long double ld;

const int MAGIC = 1234113;

bool r(){
	return rand()&(1<<10);
}

int guess(vi g)
{
	rep(i,0,g.size()) cout << g[i];
	cout << endl;
	int resp;
	cin >> resp;
	return resp;
}

void f(){/*
	int a[1000], ans[1000];
	rep(i,0,1000) a[i] = ans[i] = r();
	int g0 = guess(a);
	for(int i = 0; i < 1000; i += 2){
		a[i] ^= 1, a[i+1] ^= 1;
		int g = guess(a);
		a[i] ^= 1, a[i+1] ^= 1;
		if(g-g0 != 0){
			if(g-g0 == 2){
				ans[i] ^= 1;
				ans[i+1] ^= 1;
			}
		} else {
			a[i] ^= 1;
			if(guess(a) < g0){
				ans[i+1] ^= 1;
			} else {
				ans[i] ^= 1;
			}
			a[i] ^= 1;
		}
	}
	guess(ans);*/
	int n = 1000;
	bool cert[1000] = {};
	vi giss(1000);
	int left = n;
	vi pil[1000][2][2];
	vector<vi> fr(n), va(n), fv(n), ta(n), tv(n);
	rep(i,0,1000) giss[i] = r();
	int g0 = guess(giss);
	if(g0 == n) return;
	function<void(int,bool)> certify = [&](int u, bool bi){
		if(cert[u]) return;
		g0 += giss[u] != bi;
		giss[u] = bi;
		--left;
		cert[u] = 1;
		rep(ib,0,2) for(int v : pil[u][bi][ib])
			certify(v,ib);
		rep(i,0,fr[u].size()){
			if(cert[fr[u][i]] && giss[fr[u][i]] == fv[u][i] && va[u][i] == giss[u])
				certify(ta[u][i], tv[u][i]);
		}
	};
	while(left > 3){
		int a,b,c;
		do{a = rand()%n;} while(cert[a]);
		do{b = rand()%n;} while(cert[b] || b == a);
		do{c = rand()%n;} while(cert[c] || c == a || c == b);
		giss[a] ^= 1;giss[b] ^= 1;giss[c] ^= 1;
		int diff = guess(giss) - g0;
		if(diff == n-g0) return;
		int abc[3];
		abc[0] = a, abc[1] = b, abc[2] = c;
		if(abs(diff) == 3){
			if(diff == -3) giss[a] ^= 1, giss[b] ^= 1, giss[c] ^=1;
			else g0 += diff;
			for(int x : abc) certify(x,giss[x]);
		} else {
			if(diff == -1){
				giss[a] ^= 1, giss[b] ^= 1, giss[c] ^=1;
			} else {
				g0 += diff;
			}
			for(int x : abc) for(int y : abc) if(x != y){
				pil[x][!giss[x]][giss[y]].pb(y);
				fr[x].pb(y);
				fv[x].pb(giss[y]);
				va[x].pb(giss[x]);
				int z = abc[0]+abc[1]+abc[2]-x-y;
				ta[x].pb(z);
				tv[x].pb(!giss[z]);
			}
		}
	}
	if(g0 == n){
		guess(giss);
		return;
	}
	vi xs;
	rep(i,0,n) if(!cert[i]) xs.pb(i);
	rep(mks,1,1<<left){
		rep(i,0,left) giss[xs[i]] ^= bool(mks&(1<<i));
	    if(guess(giss) == n) return;
		rep(i,0,left) giss[xs[i]] ^= bool(mks&(1<<i));
	}
}

void init(int n){
	srand(MAGIC);
	if(n == 1000){
		f();
		return;
	}
	if(n == 1){
		vi a = {0};
		if(guess(a) == 1) return;
		a[0] = 1;
		guess(a);
		return;
	} else if(n == 2){
		vi a = {0,0};
		int g = guess(a);
		if(g == 2) return;
		if(g == 0){
			a[0] = a[1] = 1;
			guess(a);
			return;
		}
		a[0] = 1;
		if(guess(a) == 2) return;
		a[0] = 0, a[1] = 1;
		guess(a);
		return;
	}
	vi a(n);
	vi res(n-1);
	int mn = n, mx = 0;
	rep(i,0,n-1){
		a[i] = 1;
		res[i] = guess(a);
		if(res[i] == n) return;
		mn = min(mn,res[i]);
		mx = max(mx,res[i]);
		a[i] = 0;
	}
	if(mn < mx){
		int cnt = mn+1;
		rep(i,0,n-1){
			a[i] = res[i] == mx;
			cnt -= !a[i];
		}
		a[n-1] = !cnt;
		guess(a);
	} else if(n == 3){
		a[2] = mn == 1;
		if(guess(a) < n){
			a[0] = a[1] = 1;
			guess(a);
		}
	} else if(n == 4){
		if(mn == 3){
			guess(a);
		} else if(mn == 1){
			rep(i,0,n) a[i]=1;
			guess(a);
		} else {
			a[3] = 1;
			if(guess(a) < n){
				rep(i,0,4) a[i] ^= 1;
				guess(a);
			}
		}
	} else {
		int b = mn <= 2;
		rep(i,0,n-1) a[i]=b;
		int cnt = mn + (b ? -1 : 1);
		rep(i,0,n-1) cnt -= !a[i];
		a[n-1] = !cnt;
		guess(a);
	}
}
int main()
{
	int n;
	cin >> n;
	init(n);
}