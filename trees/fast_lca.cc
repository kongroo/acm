#include <bits/stdc++.h>
using namespace std;

struct FastLCA {
  template <class T> struct STable {
    vector<vector<T>> f;
    function<T(T, T)> op;
    STable() {}
    STable(const vector<T> &a, function<T(T, T)> op) : f(32 - __builtin_clz(a.size()), a), op(op) {
      for (size_t c = 0; c + 1 < f.size(); c++)
        for (size_t i = 0; i < a.size(); i++)
          f[c + 1][i] = i + (1 << c) < a.size() ? op(f[c][i], f[c][i + (1 << c)]) : f[c][i];
    }
    T query(int l, int r) const {
      int c = 31 - __builtin_clz(r - l);
      return op(f[c][l], f[c][r - (1 << c)]);
    }
  };
  int n, b;
  vector<int> dep, dfn, order, block_type;
  vector<vector<int>> dict;
  STable<int> st;

  FastLCA(const vector<vector<int>> &g, int root) : dep(g.size()), dfn(dep) {
    auto dfs = [&](int u, int p, int d, auto fn) -> void {
      dfn[u] = order.size(), order.push_back(u), dep[u] = d;
      for (int v : g[u])
        if (v != p) fn(v, u, d + 1, fn), order.push_back(u);
    };
    dfs(root, root, 0, dfs);
    n = order.size(), b = ceil(log2(n + 1) / 2);
    // inter block
    vector<int> block_mins;
    for (int i = 0; i < n; i += b) {
      int mi = order[i];
      for (int j = i; j < n && j < i + b; ++j)
        if (dep[order[j]] < dep[mi]) mi = order[j];
      block_mins.push_back(mi);
    }
    st = STable<int>(block_mins, [&](int u, int v) { return dep[u] < dep[v] ? u : v; });
    // inner block
    dict.assign(1 << b, vector<int>(b * b));
    block_type.resize(block_mins.size());
    for (int mask = 0; mask < (1 << b); ++mask) {
      for (int i = 0; i < b; ++i) {
        for (int j = i, min_val = INT_MAX, min_pos = i, cur = 0; j < b; ++j) {
          cur += mask & (1 << j) ? 1 : -1;
          if (cur < min_val) min_pos = j, min_val = cur;
          dict[mask][i * b + j] = min_pos;
        }
      }
    }
    for (int i = 0; i < n; i += b) {
      int mask = 0;
      for (int j = 1; j < b && i + j < n; ++j)
        if (dep[order[i + j]] > dep[order[i + j - 1]]) mask |= 1 << j;
      block_type[i / b] = mask;
    }
  }
  int lca(int u, int v) const {
    auto [l, r] = minmax(dfn[u], dfn[v]);
    int bl = l / b, br = r / b, pl = l % b, pr = r % b;
    if (bl == br)
      return order[bl * b + dict[block_type[bl]][pl * b + pr]];
    else {
      int x = order[bl * b + dict[block_type[bl]][pl * b + b - 1]];
      int y = order[br * b + dict[block_type[br]][pr]];
      if (dep[y] < dep[x]) x = y;
      if (bl + 1 < br) {
        int z = st.query(bl + 1, br);
        if (dep[z] < dep[x]) x = z;
      }
      return x;
    }
  }
  int dist(int u, int v) const {
    int an = lca(u, v);
    return abs(dep[an] - dep[u]) + abs(dep[an] - dep[v]);
  }
};

// Luogu. P3379
int main() {
  int n, m, s;
  scanf("%d%d%d", &n, &m, &s);
  vector<vector<int>> g(n + 1);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  FastLCA fl(g, s);
  while (m--) {
    int u, v;
    scanf("%d%d", &u, &v);
    printf("%d\n", fl.lca(u, v));
  }
}