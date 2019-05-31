#include <bits/stdc++.h>
using namespace std;

struct DSU : vector<int> {
  DSU(int n) { this->assign(n, -1); }
  int root(int x) { return at(x) < 0 ? x : at(x) = root(at(x)); }
  int size(int x) { return -at(root(x)); }
  bool same(int x, int y) { return root(x) == root(y); }
  bool unite(int x, int y) {
    x = root(x), y = root(y);
    if (x != y) {
      if (at(y) < at(x)) std::swap(x, y);
      at(x) += at(y), at(y) = x;
    }
    return x != y;
  }
};
