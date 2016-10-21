#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int surveillance(int B, int W, int S[1000][1000], int T[1000][1000]) {
  int diff = S[0][0] - T[0][0];
  rep(i,0,B)
    rep(j,0,B)
      if(S[i][j] != T[i][j] + dif) return 0;
  return 1;
}
