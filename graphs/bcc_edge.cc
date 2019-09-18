#include <bits/stdc++.h>
using namespace std;

// return Low array as color array
// reverse edge should be update by min(low[u], dfn[v]),
// but for edge bcc, it seems ok to use min(low[u], low[v])
vector<int> bcc_edge(const vector<vector<int>>& g) {
  int n = int(g.size()), ts = 0, t = 0;
  vector<int> dfn(n), low(n), st(n + 1);
  auto dfs = [&](int u, int p, auto f) -> void {
    low[u] = dfn[u] = ++ts, st[t++] = u;
    for (auto v : g[u]) if (v != p) {
      if (!dfn[v]) f(v, u, f);
      low[u] = min(low[u], low[v]);
    }
    if (dfn[u] == low[u]) while (t && st[t] != u) low[st[--t]] = low[u];
  };
  for (int i = 0; i < n; i++) if (!dfn[i]) dfs(i, -1, dfs);
  return low;
}


// CF. 1220E
using LL = long long;
const int N = 2e5 + 5;
int n, nn, m, w[N], s;
LL total[N], f[N][2];
char h[N];
vector<vector<int>> g, gg, pt;
vector<int> color;

LL dp(int u, int p, bool ret) {
  if (f[u][ret] != -1) return f[u][ret];
  LL ans = total[u];
  if (pt[u].size() > 1) h[u] = true;
  for (int v: gg[u]) {
    if (v == p) continue;
    dp(v, u, true);
    if (!h[v]) continue;
    ans += dp(v, u, true);
    h[u] = true;
  }
  if (!ret) {
    LL mans = ans;
    for (int v: gg[u]) {
      if (v == p) continue;
      if (!h[v]) mans = max(mans, ans + dp(v, u, false));
      else mans = max(mans, ans + dp(v, u, false) - dp(v, u, true));
    }
    ans = mans;
  }
  return f[u][ret] = ans;
}

int main() {
  memset(f, -1, sizeof f);
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) scanf("%d", &w[i]);
  g.resize(n + 1);
  for (int i = 1; i <= m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  scanf("%d", &s);
  color = bcc_edge(g);
  nn = *max_element(color.begin(), color.end()) + 1;
  gg.resize(nn + 1), pt.resize(nn + 1);
  for (int u = 1; u <= n; ++u) {
    pt[color[u]].push_back(u);
    for (int v: g[u]) {
      if (color[v] == color[u]) continue;
      gg[color[u]].push_back(color[v]);
    }
  }
  for (int i = 0; i < nn; ++i) {
    sort(gg[i].begin(), gg[i].end());
    gg[i].resize(unique(gg[i].begin(), gg[i].end()) - gg[i].begin());
  } 
  for (int u = 1; u <= n; ++u) total[color[u]] += w[u];
  cout << dp(color[s], -1, false) << endl;
}
