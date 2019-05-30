#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct MinCostFlow {
  struct Edge {
    int u, v;
    T c, w, f;
  };
  const T eps = T(1e-9), INF = numeric_limits<T>::max();
  vector<Edge> E;
  int n, src, sink;
  vector<vector<int>> G;
  T flow = T(), cost = T();
  MinCostFlow(int n, int src, int sink) : n(n), src(src), sink(sink), G(n) {}

  void clear_flow() {
    for (auto& e : E) e.f = T();
    flow = cost = T();
  }
  void reduce() {
    for (auto& e : E) e.c -= e.f;
  }
  void add_edge(int u, int v, T cap, T cost) {
    assert(0 <= u && u < n && 0 <= v && v < n);
    G[u].push_back(E.size()), E.push_back({u, v, cap, cost, T()});
    G[v].push_back(E.size()), E.push_back({v, u, 0, -cost, T()});
  }
  T min_cost_flow(T f = -1) {
    if (f < 0) f = INF;
    if (flow > f) clear_flow();
    f -= flow;
    while (f > eps) {
      vector<T> D(n, INF);
      vector<int> Inq(n), P(n);
      queue<int> Q;
      Q.push(src), D[src] = T(), Inq[src] = 1;
      while (!Q.empty()) {
        int u = Q.front();
        Q.pop(), Inq[u] = 0;
        for (auto i : G[u]) {
          const auto& e = E[i];
          if (e.c - e.f > eps && D[e.v] > D[u] + e.w) {
            D[e.v] = D[u] + e.w, P[e.v] = i;
            if (!Inq[e.v]) Q.push(e.v), Inq[e.v] = 1;
          }
        }
      }
      if (D[sink] == INF) break;
      T can = f;
      for (int u = sink; u != src; u = E[P[u]].u) can = min(can, E[P[u]].c - E[P[u]].f);
      f -= can, flow += can, cost += D[sink] * can;
      for (int u = sink; u != src; u = E[P[u]].u) E[P[u]].f += can, E[P[u] ^ 1].f -= can;
    }
    return cost;
  }
};

// 51Nod. 1392
int main() {
  int n;
  scanf("%d", &n);
  vector<array<int, 2>> A(n + 1);
  for (int i = 1; i <= n; i++) scanf("%d%d", &A[i][0], &A[i][1]);
  sort(A.begin() + 1, A.end());
  A.erase(unique(A.begin() + 1, A.end()), A.end());
  n = A.size() - 1;
  int src = 0, sink = 2 * n + 1;
  MinCostFlow<double> G(n * 2 + 2, src, sink);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    ans += A[i][0] * A[i][1];
    G.add_edge(src, i, 1, 0);
    G.add_edge(i + n, sink, 1, 0);
    for (int j = 1; j <= n; j++) {
      if (i == j || A[j][0] < A[i][0] || A[j][1] < A[i][1]) continue;
      G.add_edge(i, j + n, 1, -A[i][0] * A[i][1]);
    }
  }
  printf("%d\n", ans + (int)G.min_cost_flow());
  return 0;
}
