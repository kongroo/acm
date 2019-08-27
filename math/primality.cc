#include <bits/stdc++.h>
using namespace std;

namespace Primality {
using LL = long long;
constexpr LL mmul(LL x, LL y, LL m) {
  LL ret = x * y - (LL)((long double)x * y / m + 0.5) * m;
  return ret < 0 ? ret + m : ret;
}
constexpr LL mpow(LL x, LL y, LL m) {
  LL s = 1;
  for (LL c = x % m; y; c = mmul(c, c, m), y >>= 1)
    if (y & 1) s = mmul(s, c, m);
  return s;
}
bool miller_rabin(LL n) {
  static const vector<int> base = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
  if (n <= 3) return n >= 2;
  if (~n & 1) return false;
  for (size_t i = 1; i < base.size(); i++)
    if (n != base[i] && !(n % base[i])) return false;
  LL e = n - 1, a = 0, c = 0;
  while (~e & 1) e /= 2, c++;
  for (int i = 0, t = n < 1e6 ? 2 : n < 3e9 ? 4 : n < 2e12 ? 5 : n < 3e18 ? 9 : 12; i < t; i++) {
    a = mpow(base[i], e, n);
    if (a == 1) continue;
    for (int j = 1; a != n - 1; j++) {
      if (j == c) return false;
      a = mmul(a, a, n);
    }
  }
  return true;
}
LL pollard_rho(LL n) {
  static mt19937 gen = mt19937(random_device()());
  if (n <= 3 || miller_rabin(n)) return n;
  uniform_int_distribution<LL> ud(0, n - 1);
  for (;;) {
    int i = 1, cnt = 2;
    LL x = ud(gen), y = x, c = ud(gen);
    if (!c || c == n - 2) c++;
    do {
      LL u = __gcd(n - x + y, n);
      if (u > 1 && u < n) return u;
      if (++i == cnt) y = x, cnt *= 2;
      x = (c + mmul(x, x, n)) % n;
    } while (x != y);
  }
}
vector<LL> factorize(LL n) {
  vector<LL> u;
  for (auto x : {2, 3, 5, 7, 11, 13}) {
    while (n % x == 0) n /= x, u.push_back(x);
  }
  if (n > 1) u.push_back(n);
  for (size_t i = u.size() - 1; i < u.size(); i++) {
    LL x = pollard_rho(u[i]);
    if (x == u[i]) continue;
    u[i--] /= x;
    u.push_back(x);
  }
  sort(u.begin(), u.end());
  return u;
}
};  // namespace Primality

const int N = 1e8;
bitset<N> bs;

int main() {
  for (int i = 2; i * i < N; i++) {
    if (!bs.test(i)) {
      for (int j = i * i; j < N; j += i) bs.set(j);
    }
  }
  for (int i = 2; i < N; i++) {
    if (bs.test(i) == Primality::miller_rabin(i)) {
      cout << i << endl;
      return 0;
    }
  }
  cout << Primality::miller_rabin(1e9 + 7) << endl;
  return 0;
}
