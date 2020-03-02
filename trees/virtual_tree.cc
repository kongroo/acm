#include <bits/stdc++.h>
using namespace std;

// Luogu. P6135
const int N = 2e5 + 5;
int root, dep[N], fa[N][20], dfn[N], ts = 0;
pair<int, int> ans[N];
vector<int> g[N];
vector<pair<int, int>> vg[N];

void dfs(int u, int p, int d) {
  dep[u] = d, dfn[u] = ++ts;
  fa[u][0] = p;
  for (int i = 1; i < 20; ++i) fa[u][i] = fa[fa[u][i - 1]][i - 1];
  for (int v : g[u]) {
    if (v == p) continue;
    dfs(v, u, d + 1);
  }
}

void dfsv(int u, int p) {
  for (auto [v, len] : vg[u]) {
    if (v == p) continue;
    ans[v] = {u, len};
    dfsv(v, u);
  }
}

int lca(int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  int d = dep[u] - dep[v];
  for (int i = 0; i < 20; ++i)
    if (d & 1 << i) u = fa[u][i];
  if (u == v) return u;
  for (int i = 19; i >= 0; --i)
    if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
  return fa[u][0];
}

void connect(int u, int v) {
  int dist = abs(dep[u] - dep[v]);
  vg[u].emplace_back(v, dist);
  vg[v].emplace_back(u, dist);
}

void build_vtree(vector<int> key_nodes) {
  sort(key_nodes.begin(), key_nodes.end(), [&](int u, int v) { return dfn[u] < dfn[v]; });
  vector<int> st;
  root = -1;
  auto ins = [&](int u) { 
    st.push_back(u), vg[u].clear(); 
    if (root == -1 || dep[u] < dep[root]) root = u;
  };
  for (int u : key_nodes) {
    if (!st.empty()) {
      int an = lca(u, st.back());
      if (an != st.back()) {
        vector<int> link;
        while (!st.empty() && dfn[st.back()] > dfn[an]) link.push_back(st.back()), st.pop_back();
        reverse(link.begin(), link.end());
        if (st.empty() || st.back() != an) ins(an);
        connect(an, link.front());
        for (int i = 0, sz = link.size(); i + 1 < sz; ++i) connect(link[i], link[i + 1]);
      }
    }
    ins(u);
  }
  for (int i = 0, sz = st.size(); i + 1 < sz; ++i) connect(st[i], st[i + 1]);
}

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i) {
    int pa;
    scanf("%d", &pa);
    if (pa == 0)
      root = i;
    else
      g[pa].push_back(i), g[i].push_back(pa);
  }
  dfs(root, root, 0);
  vector<int> key_nodes;
  for (int i = 0, x; i < k; ++i) {
    scanf("%d", &x);
    key_nodes.push_back(x);
  }
  build_vtree(key_nodes);
  for (int i = 1; i <= n; ++i) ans[i] = {-1, -1};
  ans[root] = {0, 0};
  dfsv(root, root);
  for (int i = 1; i <= n; ++i) printf("%d %d\n", ans[i].first, ans[i].second);
}