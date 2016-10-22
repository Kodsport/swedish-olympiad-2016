#include <bits/stdc++.h>
using namespace std;
long long fibonacci(int N, char X[]) {
  int left[N];
  int right[N];
  { 
    int include = 0;
    char prev = 'b';
    for (int i = 0; i < N; ++i) {
      if (prev == 'a' && X[i] == 'a') include = i;
      left[i] = i - include + 1;
      prev = X[i];
    }
  }

  {
    int include = N - 1;
    char prev = 'b';
    for (int i = N - 1; i >= 0; --i) {
      if (prev == 'a' && X[i] == 'a') include = i;
      right[i] = include - i + 1;
      prev = X[i];
    }
  }
  long long ans = 0;
  for (int i = 0; i < N; ++i) {
    if (X[i] == 'a') ans += (long long)left[i] * right[i];
  }
  return ans;
}
