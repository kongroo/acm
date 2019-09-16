#include <bits/stdc++.h>
using namespace std;

struct TwoSat {
  int n;
  vector<vector<int>> g, gr;
  vector<char> used, answer;
  vector<int> order, comp;

  TwoSat(int n): n(n), g(n * 2), gr(n * 2) {}
  void add(int x, int y, bool nx, bool ny) { 
    auto add_ = [&](int u, int v) { g[u].push_back(v), gr[v].push_back(u); }; 
    add_(x * 2 + !nx, y * 2 + ny), add_(y * 2 + !ny, x * 2 + nx);
  }
  void dfs1(int u) {
    used[u] = true;
    for (int v: g[u]) if (!used[v]) dfs1(v);
    order.push_back(u);
  }
  void dfs2(int u, int c) {
    comp[u] = c;
    for (int v: gr[u]) if (comp[v] == -1) dfs2(v, c);
  }
  bool solve() {
    order.clear(), used.assign(n * 2, false), comp.assign(n * 2, -1), answer.assign(n, false);
    for (int u = 0; u < n * 2; ++u) if (!used[u]) dfs1(u);
    for (int i = 0, j = 0; i < n * 2; ++i) {
      int u = order[2 * n - 1 - i];
      if (comp[u] == -1) dfs2(u, j++);
    }
    for (int i = 0; i < n; ++i) {
      if (comp[i << 1] == comp[i << 1 | 1]) return false;
      answer[i] = comp[i << 1] > comp[i << 1 | 1];
    }
    return true;
  }
};


// CF. 1215F
int main() {
  int n, p, M, m;
  scanf("%d%d%d%d", &n, &p, &M, &m);
  vector<int> x(n), y(n), l(p), r(p), u(m), v(m);
  for (int i = 0; i < n; ++i) scanf("%d%d", &x[i], &y[i]);
  for (int i = 0; i < p; ++i) scanf("%d%d", &l[i], &r[i]);
  for (int i = 0; i < m; ++i) scanf("%d%d", &u[i], &v[i]);

  TwoSat ts(p + M + 2);
  for (int i = 0; i < n; ++i) ts.add(x[i], y[i], 0, 0);
  for (int i = 0; i < m; ++i) ts.add(u[i], v[i], 1, 1);
  for (int i = 0; i < p; ++i) ts.add(i + 1, l[i] + p, 1, 0), ts.add(i + 1, r[i] + 1 + p, 1, 1);
  for (int i = 1; i <= M; ++i) ts.add(i + p, i + p + 1, 0, 1);
  if (!ts.solve()) return puts("-1"), 0;
  vector<int> selected;
  for (int i = 1; i <= p; ++i) if (ts.answer[i]) selected.push_back(i);
  int k = 0;
  for (int i = 1; i <= M && ts.answer[i + p]; ++i) ++k;
  cout << selected.size() << ' ' << k << endl;
  for (auto x: selected) printf("%d ", x);
  puts("");
}
