#include <bits/stdc++.h>

using namespace std;

int main(){
  const string S = "UUNNVHVHBA";
  string s;
  cin >> s;
  int L = (int)S.size(), len = (int)s.size(), ans = len;

  assert(len <= 3000);

  for (int i = 0; i < len; ++i) {
    int at = 0;
    int j = i;
    while(j < len && at != L) {
      if(s[j] == S[at]) at++;
      j++;
    }
    if(at == L) ans = min(ans, j - i);
  }

  cout << ans - L << endl;
}
