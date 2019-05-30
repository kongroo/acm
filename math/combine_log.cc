#include <bits/stdc++.h>
using namespace std;

/*
 * C(n, k) = C(n-1, k) + C(n-1, k-1), C(n, k) = C(n, k-1) * (n-k+1) / k
 * C(n, 0) + C(n, 1) + ... + C(n, n) = 2^n
 * C(n, 1) + ... = C(n, 0) + ... = 2^(n-1)
 * C(n, 0)^2 + ... + C(n, n)^2 = C(2*n, n)
 */

struct Combine {
  using LL = long long;
  int m;
  vector<LL> F;
  Combine(int n, int m) : m(m), F(n, 1) {
    for (int i = 1; i < n; i++) F[i] = F[i - 1] * i % m;
  }
  int inv(LL x) { return x > m ? inv(x % m) : x > 1 ? inv(m % x) * (m - m / x) % m : x; }
  int com(LL n, LL k) { return F.at(n) * inv(F.at(n - k) * F[k]) % m; }
  int per(LL n, LL k) { return F.at(n) * inv(F.at(k)) % m; }
};

int main() {}
