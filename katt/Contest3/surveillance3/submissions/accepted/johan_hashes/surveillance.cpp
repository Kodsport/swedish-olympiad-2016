#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

typedef unsigned long long H;
static const H C = 123891739; // arbitrary

// Arithmetic mod 2^64-1. 5x slower than mod 2^64 and more
// code, but works on evil test data (e.g. Thue-Morse).
// "typedef H K;" instead if you think test data is random.
struct K {
  typedef __uint128_t H2;
  H x; K(H x=0) : x(x) {}
  K operator+(K o){ return x + o.x + H(((H2)x + o.x)>>64); }
  K operator*(K o){ return K(x*o.x)+ H(((H2)x * o.x)>>64); }
  H operator-(K o) { K a = *this + ~o.x; return a.x + !~a.x; }
};

struct HashInterval {
  vector<K> ha, pw;
  HashInterval(vi& str) : ha(sz(str)+1), pw(ha) {
    pw[0] = 1;
    rep(i,0,sz(str))
      ha[i+1] = ha[i] * C + str[i],
      pw[i+1] = pw[i] * C;
  }
  H hashInterval(int a, int b) { // hash [a, b)
    return ha[b] - ha[a] * pw[b - a];
  }
};

template<class T>
vector<H> getHashes(vector<T>& str, int length) {
  if (sz(str) < length) return {};
  K h = 0, pw = 1;
  rep(i,0,length)
    h = h * C + str[i], pw = pw * C;
  vector<H> ret = {h - 0};
  rep(i,length,sz(str)) {
    ret.push_back(h * C + str[i] - pw * str[i-length]);
    h = ret.back();
  }
  return ret;
}

H hashString(vi& s) {
  K h = 0;
  trav(c, s) h = h * C + c;
  return h - 0;
}

typedef vector<H> vh;
vector<vh> rectHashes(int B, int S[1000][1000], int W) {
  vector<vh> rowHashes(B - 1);
  rep(i,0,B-1){
    vi diffs(B);
    rep(j,0,B) diffs[j] = S[i][j] >= S[i + 1][j] ? S[i][j] - S[i + 1][j] : ~(S[i + 1][j] - S[i][j]);
    rowHashes[i] = getHashes(diffs, W);
  }
  vector<vh> hashes(B - W + 1, vh(B - W + 1));
  rep(i,0,B-W+1){
    vh diffs(B - 1);
    rep(j,0,B-1) diffs[j] = rowHashes[j][i];
    vh colHashes = getHashes(diffs, W - 1);
    rep(j,0,B-W+1) hashes[j][i] = colHashes[j];
  }
  return hashes;
}

int surveillance(int B, int W, int S[1000][1000], int T[1000][1000]) {
  vector<vh> bhashes = rectHashes(B, S, W);
  H whash = rectHashes(W, T, W)[0][0];
  rep(i,0,B) rep(j,0,i) swap(S[i][j], S[j][i]);
  rep(i,0,W) rep(j,0,i) swap(T[i][j], T[j][i]);
  vector<vh> bhashes2 = rectHashes(B, S, W);
  H whash2 = rectHashes(W, T, W)[0][0];
  int ans = 0;
  rep(i,0,B-W+1) rep(j,0,B-W+1) ans += (whash == bhashes[i][j]) * (whash2 == bhashes2[j][i]); return ans;
}
