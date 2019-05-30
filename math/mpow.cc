#include <bits/stdc++.h>
using namespace std;

constexpr long long mpow(long long a, long long k, long long m) {
  long long r(1);
  for (a %= m; k; k >>= 1, a = a * a % m)
    if (k & 1) r = r * a % m;
  return r;
}

int main() { return 0; }
