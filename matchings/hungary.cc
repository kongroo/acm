#include <bits/stdc++.h>
using namespace std;

vector<int> hungary(const vector<vector<int>>& G) {
  vector<int> M(G.size(), -1);
  vector<char> B(G.size(), 0);
  auto dfs = [&](int u, int p, auto f) -> bool {
    B[u] = 1;
    if (M[u] < 0 && p != -1) return true;
    if (M[u] >= 0 && M[u] != p) return f(M[u], u, f);
    for (auto v : G[u])
      if (v != p && !B[v] && f(v, u, f)) return M[u] = v, M[v] = u, 1;
    return 0;
  };
  for (size_t i = 0; i < G.size(); ++i)
    if (M[i] < 0) fill(B.begin(), B.end(), 0), dfs(i, -1, dfs);
  return M;
}

int main() {
  int n, m, e;
  scanf("%d%d%d", &n, &m, &e);
  vector<vector<int>> G(n + m + 1);
  for (int i = 0; i < e; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    if (v > m) continue;
    G[u].push_back(v + n);
    G[v + n].push_back(u);
  }
  auto M = hungary(G);
  int ans = 0;
  for (int i = 1; i <= n; i++)
    if (M[i] >= 0) ans++;
  printf("%d\n", ans);
  return 0;
}
