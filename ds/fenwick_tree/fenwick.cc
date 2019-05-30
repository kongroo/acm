#include <bits/stdc++.h>
using namespace std;

template <class T>
struct Fenwick {
  vector<T> V;
  Fenwick(int n) : V(n) {}
  void add(size_t i, T x) {
    for (; i < V.size(); i |= i + 1) V[i] += x;
  }
  T sum(int i) {
    T r = T();
    for (--i; i >= 0; i = (i & (i + 1)) - 1) r += V[i];
    return r;
  }
  T sum(int l, int r) { return sum(r) - sum(l); }
};

int main() {
  int n = 30;
  using B = bitset<6>;
  for (int i = 0; i <= n; i++) {
    cout << i << ' ' << B(i) << ' ' << B(i | (i + 1)) << ' ' << B((i & (i + 1)) - 1) << endl;
  }
  return 0;
}
