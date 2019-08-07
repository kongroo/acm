#include <bits/stdc++.h>
using namespace std;

/* template <class T> struct Fenwick {
  vector<T> v;
  Fenwick(int n) : v(n) {}
  void add(size_t i, T x) { for (; i < v.size(); i |= i + 1) v[i] += x; }
  T sum(int i) {
    T r = T();
    for (--i; i >= 0; i = (i & (i + 1)) - 1) r += v[i];
    return r;
  }
  T sum(int l, int r) { return sum(r) - sum(l); }
}; */

template <class T> struct Fenwick {
  vector<T> v;
  Fenwick(size_t n) : v(n + 1) {}
  void add(size_t i, T x) { for (++i; i < v.size(); i += i & -i) v[i] += x; }
  T sum(size_t i) { for (v[0] = T(); i; i -= i & -i) v[0] += v.at(i); return v[0]; }
  T sum(size_t l, size_t r) { return sum(r) - sum(l); }
};

int main() {
  int n = 30;
  using B = bitset<6>;
  for (int i = 0; i <= n; i++) {
    cout << i << ' ' << B(i) << ' ' << B(i | (i + 1)) << ' ' << B((i & (i + 1)) - 1) << endl;
  }
  return 0;
}
