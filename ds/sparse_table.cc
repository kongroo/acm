#include <bits/stdc++.h>
using namespace std;

template <class T> struct STable {
  vector<vector<T>> f;
  function<T(T, T)> op;
  STable(const vector<T>& a, function<T(T, T)> op = [](T a, T b) { return min(a, b); })
      : f(32 - __builtin_clz(a.size()), a), op(op) {
    for (size_t c = 0; c + 1 < f.size(); c++)
      for (size_t i = 0; i < a.size(); i++)
        f[c + 1][i] = i + (1 << c) < a.size() ? op(f[c][i], f[c][i + (1 << c)]) : f[c][i];
  }
  T query(int l, int r) {
    int c = 31 - __builtin_clz(r - l);
    return op(f[c][l], f[c][r - (1 << c)]);
  }
};

int main() {
  STable<int> st(vector<int>(1000), [](int a, int b) { return max(a, b); });
}
