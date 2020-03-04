#include <bits/stdc++.h>
using namespace std;

struct Sieve {
  vector<int> low, phi, pr;
  Sieve(int n) : low(n), phi(n, 1) {
    low[1] = 1;
    for (int x = 2; x < n; x++) {
      if (!low[x]) pr.push_back(low[x] = x), phi[x] = x - 1;
      for (auto p : pr) {
        if (x * p >= n) break;
        low[x * p] = p;
        phi[x * p] = phi[x] * (p - (x % p != 0));
        if (x % p == 0) break;
      }
    }
  }

  vector<long long> factorize(long long n) {
    vector<long long> ret;
    for (int i = 0; 1ll * pr[i] * pr[i] <= n; i++) {
      if (n % pr[i]) continue;
      do {
        n /= pr[i], ret.push_back(pr[i]);
      } while (n % pr[i] == 0);
    }
    if (n > 1) ret.push_back(n);
    return ret;
  }
  vector<int> factorize_low(int n) {
    assert(n < (int)low.size());
    vector<int> ret;
    while (n != 1) ret.push_back(low[n]), n /= low[n];
    return ret;
  }
};

// 51Nod. 1188
int main() {
  using LL = long long;
  const int N = 5000000;
  auto sv = new Sieve(N + 1);
  vector<LL> Ans(N + 1);
  for (int i = 1; i <= N; i++)
    for (int j = 2; i * j <= N; j++) Ans[i * j] += i * sv->Phi[j];
  for (int i = 1; i <= N; i++) Ans[i] += Ans[i - 1];
  int t;
  scanf("%d", &t);
  while (t--) {
    int n;
    scanf("%d", &n);
    printf("%lld\n", Ans[n]);
  }
  return 0;
}
