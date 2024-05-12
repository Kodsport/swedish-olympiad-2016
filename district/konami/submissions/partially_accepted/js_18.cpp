#include <bits/stdc++.h>

using namespace std;

int main(){
  const string S = "UUNNVHVHBA";
  string s;
  cin >> s;
  int L = (int)S.size(), len = (int)s.size(), ans = len;
  assert(len <= 200);
  for (int i = 0; i < len; ++i) {
    for(int j = i; j < len; ++j){
      int found = 0;
      for(int k = i; k <= j && found != L; ++k) {
        if(s[k] == S[found]) found++;
      }
      if (found == L) ans = min(ans, j - i + 1);
    }
  }

  cout << ans - L << endl;
}
