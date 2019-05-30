#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct MaxFlow {
  struct Edge {
    int u, v;
    T c, f;
  };
  const T eps = (T)1e-9;
  vector<Edge> E;
  int n, src, sink;
  vector<vector<int>> G;
  vector<int> P, D;
  T flow = T();
  MaxFlow(int n, int src, int sink) : n(n), src(src), sink(sink), G(n), P(n), D(n) {}

  void clear_flow() {
    for (auto& e : E) e.f = T();
    flow = T();
  }
  void reduce() {
    for (auto& e : E) e.c -= e.f;
  }
  void add_edge(int u, int v, T cap) {
    assert(0 <= u && u < n && 0 <= v && v < n);
    G[u].push_back(E.size()), E.push_back({u, v, cap, T()});
    G[v].push_back(E.size()), E.push_back({v, u, T(), T()});
  }
  bool expath() {
    fill(D.begin(), D.end(), -1);
    queue<int> Q;
    Q.push(sink), D[sink] = 0;
    while (!Q.empty()) {
      int u = Q.front();
      Q.pop();
      for (int id : G[u]) {
        const Edge &e = E[id], &b = E[id ^ 1];
        if (b.c - b.f > eps && D[e.v] == -1) {
          D[e.v] = D[e.u] + 1, Q.push(e.v);
          if (e.v == src) return true;
        }
      }
    }
    return false;
  }
  T dfs(int u, T w) {
    if (u == sink) return w;
    for (int& i = P[u]; i < int(G[u].size()); i++) {
      int id = G[u][i];
      const Edge& e = E[id];
      if (e.c - e.f > eps && D[e.v] == D[e.u] - 1) {
        T t = dfs(e.v, min(e.c - e.f, w));
        if (t > eps) return E[id].f += t, E[id ^ 1].f -= t, t;
      }
    }
    return T();
  }
  const T max_flow() {
    while (expath()) {
      fill(P.begin(), P.end(), 0);
      T tot = T();
      for (;;) {
        T add = dfs(src, numeric_limits<T>::max());
        if (add <= eps) break;
        tot += add;
      }
      if (tot <= eps) break;
      flow += tot;
    }
    return flow;
  }
  vector<int> min_cut() {
    max_flow();
    vector<int> R(n);
    for (int i = 0; i < n; i++) R[i] = (D[i] != -1);
    return R;
  }
};

// 51Nod. 1757
vector<int> Dis[2001];
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<vector<int>> G(n + 1);
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    G[u].push_back(v), G[v].push_back(u);
  }
  vector<int> I(m + 1);
  for (int i = 1; i <= m; i++) {
    int id;
    scanf("%d", &id);
    I[i] = id;
    Dis[id].resize(n + 1);
    function<void(int, int, int)> dfs = [&](int u, int p, int dep) {
      Dis[id][u] = dep;
      for (auto v : G[u])
        if (v != p) dfs(v, u, dep + 1);
    };
    dfs(id, -1, 0);
  }
  auto can = [&](int t) {
    int N = 2 + n + (t + 1) * m, src = 0, sink = N - 1;
    MaxFlow<int> mf(N, src, sink);
    for (int i = 1; i <= n; i++) mf.add_edge(src, i, 1);
    for (int i = 1; i <= m; i++)
      for (int j = 0; j <= t; j++) {
        int tmp = n + (i - 1) * (t + 1) + j + 1;
        mf.add_edge(tmp, sink, 1);
        if (j) mf.add_edge(tmp - 1, tmp, n);
      }
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++)
        if (Dis[I[j]][i] <= t) mf.add_edge(i, n + (j - 1) * (t + 1) + Dis[I[j]][i] + 1, 1);
    return mf.max_flow() == n;
  };
  int l = m - 1, r = n;
  while (l + 1 < r) {
    int m = (l + r + 1) / 2;
    if (can(m))
      r = m;
    else
      l = m;
  }
  printf("%d\n", r);
  return 0;
}
