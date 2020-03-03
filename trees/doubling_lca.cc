#include <bits/stdc++.h>
using namespace std;

struct DoublingLCA {
  vector<int> dep, dfn;
  vector<vector<int>> fa;

  DoublingLCA(const vector<vector<int>> &g, int root) : dep(g.size()), dfn(dep), fa(32 - __builtin_clz(g.size()), dep) {
    int ts = 0;
    auto dfs = [&](int u, int p, int d, auto fn) -> void {
      dfn[u] = ++ts, dep[u] = d;
      fa[0][u] = p;
      for (int i = 1; i < fa.size(); ++i) fa[i][u] = fa[i - 1][fa[i - 1][u]];
      for (int v : g[u])
        if (v != p) fn(v, u, d + 1, fn);
    };
    dfs(root, root, 0, dfs);
  }
  int lca(int u, int v) const {
    if (dep[u] < dep[v]) swap(u, v);
    int d = dep[u] - dep[v];
    for (int i = 0; i < fa.size(); ++i)
      if (d & 1 << i) u = fa[i][u];
    if (u == v) return u;
    for (int i = fa.size() - 1u; i >= 0; --i)
      if (fa[i][u] != fa[i][v]) u = fa[i][u], v = fa[i][v];
    return fa[0][u];
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
  DoublingLCA dl(g, s);
  while (m--) {
    int u, v;
    scanf("%d%d", &u, &v);
    printf("%d\n", dl.lca(u, v));
  }
}