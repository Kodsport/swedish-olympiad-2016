#include <bits/stdc++.h>

using namespace std;

int main(){
  const string S = "?UUNNVHVHBA";
  string s;
  cin >> s;
  int L = (int)S.size(), len = (int)s.size(), ans = len;
  vector<int> ptrs(L);
  while(true){
    for(int i = 1; i < L; ++i){
      ptrs[i] = max(ptrs[i - 1] + 1, ptrs[i]);
      while(true){
        if(ptrs[i] >= len) goto die;
        if(s[ptrs[i]] != S[i]) ptrs[i]++;
        else break;
      }
    }
    ans = min(ans, ptrs.back() - ptrs[1] + 1);
    ptrs[1]++;
  }
die: cout << ans - L + 1 << endl;
}
