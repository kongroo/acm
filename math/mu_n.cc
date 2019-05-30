#include <bits/stdc++.h>
using namespace std;

// Mu[1] = 1, if x = p1p2...pk, Mu[x] = (-1)^k, else 0
vector<int> mu_n(int n) {
  vector<int> Mu(n), L(n), P;
  Mu[1] = L[1] = 1;
  for (int x = 2; x < n; x++) {
    if (!L[x]) P.push_back(L[x] = x), Mu[x] = -1;
    for (auto p : P) {
      if (x * p >= n) break;
      L[x * p] = p;
      if (x % p == 0) {
        Mu[x * p] = 0;
        break;
      } else
        Mu[x * p] = -Mu[x];
    }
  }
  return Mu;
}

// 51Nod. 1180
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  if (n > m) swap(n, m);
  m--, n--;
  if (n == 0) return !printf(!m ? "0\n" : "1\n");
  auto Mu = mu_n(n + 1);
  auto tot = 0LL;
  for (int i = 1; i <= n; i++) {
    tot += 1LL * Mu[i] * (n / i) * (m / i);
  }
  cout << tot + 2 << endl;
  return 0;
}
