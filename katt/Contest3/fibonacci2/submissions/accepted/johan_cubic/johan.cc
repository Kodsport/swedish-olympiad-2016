#include <bits/stdc++.h>
using namespace std;
long long fibonacci(int N, char X[]) {
  assert(N <= 100);
  long long ans = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = i; j < N; ++j) {
      char prev = 'b';
      int c = 0;
      for (int k = i; k <= j; ++k) {
        if (prev == 'a' && X[k] == 'a') goto die;
        if (X[k] == 'a') c++;
        prev = X[k];
      }
      ans += c;
die:;
    }
  }
  return ans;
}
