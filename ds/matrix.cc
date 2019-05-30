#include <bits/stdc++.h>
using namespace std;

// n x m matrix
template <typename T>
struct Matrix {
  vector<vector<T>> D;
  using Func = function<T(T, T)>;
  Func add, mul;
  Matrix(size_t n, size_t m, Func add = plus<T>(), Func mul = multiplies<T>())
      : D(n, vector<T>(m)), add(add), mul(mul) {}

  size_t n() const { return D.size(); }
  size_t m() const { return n() == 0 ? 0 : D[0].size(); }
  vector<T>& operator[](int i) { return D[i]; }
  const vector<T>& operator[](int i) const { return D[i]; }
  Matrix<T> operator*(const Matrix<T>& N) const {
    assert(m() == N.n());
    Matrix<T> R(n(), N.m(), add, mul);
    auto [im, jm, km, tmp] = tuple(n(), N.m(), m(), T());
    for (size_t i = 0; i < im; ++i)
      for (size_t j = 0; j < jm; ++j)
        for (size_t k = 0; k < km; ++k)
          tmp = mul(D[i][k], N[k][j]), R[i][j] = k == 0 ? tmp : add(R[i][j], tmp);
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

// 51Nod. 1113
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  const int Mod = 1e9 + 7;
  Matrix<int> M(
      n + 1, n + 1, [](int x, int y) { return (x + y) % Mod; },
      [](int x, int y) -> int { return 1LL * x * y % Mod; });
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) scanf("%d", &M[i][j]);
  M = M.pow(m);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) printf("%d%c", M[i][j], " \n"[j == n]);
  }
  return 0;
}
