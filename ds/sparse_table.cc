#include <bits/stdc++.h>
using namespace std;

template <class T>
struct STable {
  vector<vector<T>> F;
  function<T(T, T)> op;
  STable(
      const vector<T>& A, function<T(T, T)> op = [](T a, T b) { return min(a, b); })
      : F(32 - __builtin_clz(A.size()), A), op(op) {
    for (size_t c = 0; c + 1 < F.size(); c++)
      for (size_t i = 0; i < A.size(); i++)
        F[c + 1][i] = i + (1 << c) < A.size() ? op(F[c][i], F[c][i + (1 << c)]) : F[c][i];
  }
  T query(int l, int r) {
    int c = 31 - __builtin_clz(r - l);
    return op(F[c][l], F[c][r - (1 << c)]);
  }
};

int main() {
  STable<int> st(vector<int>(1000), [](int a, int b) { return max(a, b); });
}
