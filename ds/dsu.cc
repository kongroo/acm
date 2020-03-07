#include <bits/stdc++.h>
using namespace std;

struct DSU {
  vector<int> f;
  DSU(int n): f(n, -1) {}
  int root(int x) { return f[x] < 0 ? x : (f[x] = root(f[x])); }
  int size(int x) { return -f[root(x)]; }
  bool same(int x, int y) { return root(x) == root(y); }
  bool unite(int x, int y) {
    x = root(x), y = root(y);
    if (x != y) {
      if (f[y] < f[x]) swap(x, y);
      f[x] += f[y], f[y] = x;
    }
    return x != y;
  }
};