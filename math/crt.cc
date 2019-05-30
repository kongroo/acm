#include <bits/stdc++.h>
using namespace std;

// x % M[i] = A[i], M[i] coprime
long long crt(const vector<int>& A, const vector<int>& M) {
  assert(A.size() == M.size());
  auto inv = [&](int x, int p, auto inv) constexpr->int {
    return x > p ? inv(x % p, p, inv) : x > 1 ? inv(p % x, p, inv) * 1LL * (p - p / x) % p : x;
  };
  auto m = 1LL, ans = 0LL;
  for (auto x : M) m *= x;
  for (size_t i = 0; i < A.size(); i++)
    ans = (ans + A[i] * m / M[i] * inv(m / M[i] % M[i], M[i], inv)) % m;
  return ans;
}

// 51Nod. 1079
int main() {
  int n;
  scanf("%d", &n);
  vector<int> A, M;
  for (int i = 0; i < n; i++) {
    int p, a;
    scanf("%d%d", &p, &a);
    A.push_back(a), M.push_back(p);
  }
  printf("%d\n", (int)crt(A, M));
  return 0;
}
