#include <bits/stdc++.h>
using namespace std;

// a ^ x % mod = val
long long disc_log(long long a, long long val, long long mod) {
  using LL = long long;
  LL d = __gcd(a, mod);
  if (d != 1 && d != mod) return -1;
  LL sq = sqrt(mod) + 2;
  auto mulmod = [&](LL a, LL b) { return (a * b) % mod; };
  auto powmod = [&](LL a, LL k) {
    LL r(1);
    for (a %= mod; k; k >>= 1, a = a * a % mod)
      if (k & 1) r = r * a % mod;
    return r;
  };
  unordered_map<LL, int> M;
  LL b = val, c = powmod(a, sq);
  for (int i = 0; i <= sq; ++i) M[b] = i, b = mulmod(b, a);
  b = c;
  for (int i = 1; i <= sq; ++i) {
    if (M.count(b)) return i * sq - M[b];
    b = mulmod(b, c);
  }
  return -1;
}

// CF. 1182E
constexpr long long inv(long long x, long long m) {
  return x > m ? inv(x % m, m) : x > 1 ? inv(m % x, m) * (m - m / x) % m : x;
}

constexpr long long mpow(long long a, long long k, long long m) {
  long long r(1);
  for (a %= m; k; k >>= 1, a = a * a % m)
    if (k & 1) r = r * a % m;
  return r;
}
using LL = long long;
const LL M = 1e9 + 7;
LL n, f1, f2, f3, c;

template <typename T>
struct Matrix : vector<vector<T>> {
  using Func = function<T(T, T)>;
  Func add, mul;
  Matrix(size_t n, size_t m, Func add = plus<T>(), Func mul = multiplies<T>())
      : add(add), mul(mul) {
    this->assign(n, vector<T>(m));
  }

  const size_t n() const { return this->size(); }
  const size_t m() const { return n() == 0 ? 0 : this->front().size(); }
  Matrix<T> operator*(const Matrix<T>& N) const {
    assert(m() == N.n());
    Matrix<T> R(n(), N.m(), add, mul);
    auto [im, jm, km, tmp] = tuple(n(), N.m(), m(), T());
    for (size_t i = 0; i < im; ++i)
      for (size_t j = 0; j < jm; ++j)
        for (size_t k = 0; k < km; ++k)
          tmp = mul((*this)[i][k], N[k][j]), R[i][j] = k == 0 ? tmp : add(R[i][j], tmp);
    return R;
  }
  Matrix<T> pow(long long k) const {
    assert(k > 0 && m() == n());
    Matrix<T> R(n(), n(), add, mul);
    bool init = true;
    for (auto t = *this; k; t = t * t, k >>= 1)
      if (k & 1) R = init ? t : R * t, init = false;
    return R;
  }
};

LL mod(LL x) { return x >= M - 1 ? x % (M - 1) + M - 1 : x; }
LL addop(LL a, LL b) { return mod(a + b); }
LL mulop(LL a, LL b) { return mod(a * b); }

int main() {
  cin >> n >> f1 >> f2 >> f3 >> c;
  Matrix<LL> mul(3, 3, addop, mulop), val(3, 1, addop, mulop);
  mul[0][1] = mul[0][0] = mul[0][2] = mul[1][0] = mul[2][1] = 1;
  mul = mul.pow(n - 3);
  val[0][0] = mod(disc_log(5, f3 * mpow(c, 3, M) % M, M));
  val[1][0] = mod(disc_log(5, f2 * mpow(c, 2, M) % M, M));
  val[2][0] = mod(disc_log(5, f1 * c % M, M));
  val = mul * val;
  cout << mpow(5, val[0][0], M) * inv(mpow(c, n, M), M) % M << endl;
}
