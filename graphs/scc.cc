#include <bits/stdc++.h>
using namespace std;

vector<int> tarjan_scc(const vector<vector<int>> &g) {
  int n = int(g.size()), ts = 0, nc = 0, t = 0;
  vector<int> color(n, -1), dfn(n), low(n), st(n + 1, -1);
  auto dfs = [&](int u, auto f) -> void {
    dfn[u] = low[u] = ++ts, st[t++] = u;
    for (int v: g[u]) {
      if (!dfn[v]) f(v, f), low[u] = min(low[u], low[v]);
      else if (color[v] < 0) low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) { while (t && st[t] != u) color[st[--t]] = nc; ++nc;  }
  };
  for (int i = 0; i < n; ++i) if (!dfn[i]) dfs(i, dfs);
  return color;
}


// Luogu. 3387
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<int> w(n);
  for (int i = 0; i < n; ++i) scanf("%d", &w[i]);
  vector<vector<int>> g(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v), --u, --v;
    g[u].push_back(v);
  }
  auto color = tarjan_scc(g);
  int nn = *max_element(color.begin(), color.end()) + 2;
  vector<int> ww(nn);
  vector<vector<int>> gg(nn);
  for (int u = 0; u < n; ++u) {
    ww[color[u]] += w[u];
    for (int v: g[u]) {
      if (color[v] == color[u]) continue;
      gg[color[u]].push_back(color[v]);
    }
  }
  vector<int> ind(nn);
  for (int i = 0; i < nn; ++i) {
    sort(gg[i].begin(), gg[i].end());
    gg[i].resize(unique(gg[i].begin(), gg[i].end()) - gg[i].begin());
    for (int j: gg[i]) ++ind[j];
  }
  vector<int> order, f(nn);
  for (int i = 0; i < nn; ++i) if (!ind[i]) order.push_back(i);
  for (int i = 0; i < int(order.size()); ++i) {
    int u = order[i];
    for (int v: gg[u]) if (!(--ind[v])) order.push_back(v);
  }
  int ans = 0;
  for (int i = nn - 1; i >= 0; --i) {
    int u = order[i];
    f[u] = ww[u];
    for (int v: gg[u]) f[u] = max(f[u], f[v] + ww[u]);
    ans = max(ans, f[u]);
  }
  cout << ans << endl;
}
