#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < int(to); ++i)
#define trav(a, x) for (auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
void PR(vi &v) { trav(x, v) cout << x << ' '; cout << endl; }

int main() {
  int N;
  cin >> N;
  rep(i,0,N/2){
    double a, b;
    cin >> a >> b;
    int ai = int(a / 22.5);
    int bi = int(b / 22.5);
    char c = char(16 * ai + bi);
    cout << c;
  }
  cout << endl;
}
