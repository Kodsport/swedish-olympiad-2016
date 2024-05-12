#include <bits/stdc++.h>

using namespace std;

int main(){
  const string S = "UUNNVHVHBA";
  string s;
  cin >> s;
  int L = (int)S.size(), len = (int)s.size(), ans = len;
  cout << (s.find(S) == string::npos ? 1 : 0) << endl;
}
