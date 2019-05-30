#include <bits/stdc++.h>
using namespace std;

namespace NTT {
// must exists n*k+1 = P, (1004535809, 3), (786433, 10)
static const int P = 998244353, G = 3;
template <typename T>
void arrange(vector<T>& A) {
  int n = A.size();
  assert(n == (n & -n));
  for (int i = 1, x = 0, y = 0; i <= n; i++) {
    if (x > y) swap(A[x], A[y]);
    x ^= i & -i, y ^= n / (i & -i) >> 1;
  }
}
// int add(int x, int y) { return x + y < P ? x + y : x + y - P; }
int add(int x, int y) { return (x + y) % P; }
int mpow(long long a, int k) {
  int r = 1;
  for (a %= P; k; k >>= 1, a = a * a % P)
    if (k & 1) r = r * a % P;
  return r;
}
template <typename T>
void fourier(vector<T>& A, int inv) {
  assert(inv == -1 || inv == 1);
  int n = 1 << (32 - __builtin_clz(A.size() - 1));
  A.resize(n), arrange(A);
  for (int l = 1; l < n; l <<= 1) {
    int wl = mpow(G, ((P - 1) / l >> 1) * (l + l + inv)), w = 1, t;
    for (int i = 0; i < l; i++, w = 1LL * w * wl % P)
      for (int s = 0; s < n; s += l + l)
        t = 1LL * w * A[s + i + l] % P, A[s + i + l] = add(A[s + i], P - t),
        A[s + i] = add(A[s + i], t);
  }
  int t = mpow(n, P - 2);
  if (inv == -1)
    for (int i = 0; i < n; i++) A[i] = 1LL * A[i] * t % P;
}
template <typename T>
vector<T> multiply(vector<T> A, vector<T> B) {
  int s = A.size() + B.size() - 1;
  A.resize(s), B.resize(s), fourier(A, 1), fourier(B, 1);
  for (size_t i = 0; i < A.size(); i++) A[i] = 1LL * A[i] * B[i] % P;
  fourier(A, -1);
  A.resize(s);
  return A;
}
};  // namespace NTT

// 51Nod. 1028
int main() {
  char s[100005], t[100005];
  scanf("%s%s", s, t);
  int n = strlen(s), m = strlen(t);
  vector<int> A, B;
  for (int i = n - 1; i >= 0; i--) A.push_back(s[i] - '0');
  for (int i = m - 1; i >= 0; i--) B.push_back(t[i] - '0');
  auto R = NTT::multiply(A, B);
  for (size_t i = 0; i < R.size(); i++) {
    if (R[i] >= 10) {
      if (i + 1u == R.size()) R.push_back(0);
      R[i + 1] += R[i] / 10;
      R[i] %= 10;
    }
  }
  reverse(R.begin(), R.end());
  for (auto c : R) printf("%d", c);
  puts("");
  return 0;
}
