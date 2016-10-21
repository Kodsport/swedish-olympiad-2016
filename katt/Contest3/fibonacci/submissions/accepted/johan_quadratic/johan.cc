#include <bits/stdc++.h>
using namespace std;
long long fibonacci(int N, char X[]) {
  assert(N <= 5000);
  long long ans = 0;
  for (int i = 0; i < N; ++i) {
    if (X[i] == 'b') continue;
    int left = i, right = i;
    while (--left >= 0) {
      if (X[left + 1] == 'a' && X[left] == 'a') break;
    }
    while (++right < N) {
      if (X[right - 1] == 'a' && X[right] == 'a') break;
    }
    ans += (i - left) * (right - i);
  }
  return ans;
}
