#include <bits/stdc++.h>
using namespace std;

template <typename T, class ST>
struct HLDPoint {
  size_t n;
  vector<int> Size, Dep, Fa, Son, Top, P;
  ST* st;

  HLDPoint(const vector<vector<int>>& G, const vector<T>& A, int root)
      : n(G.size()), Size(n, -1), Dep(n, -1), Fa(n, -1), Son(n, -1), Top(n, -1), P(n, -1) {
    function<void(int, int, int)> dfs1 = [&](int u, int p, int dep) {
      Size[u] = 1;
      Dep[u] = dep;
      Fa[u] = p;
      for (auto v : G[u]) {
        if (v != p) {
          dfs1(v, u, dep + 1);
          Size[u] += Size[v];
          if (Son[u] == -1 || Size[v] > Size[Son[u]]) Son[u] = v;
        }
      }
    };
    dfs1(root, -1, 0);
    int ts = 0;
    function<void(int, int, int)> dfs2 = [&](int u, int p, int t) {
      P[u] = ts++;
      Top[u] = t;
      if (Son[u] == -1) return;
      dfs2(Son[u], u, t);
      for (auto v : G[u]) {
        if (v != p && v != Son[u]) dfs2(v, u, v);
      }
    };
    dfs2(root, -1, root);
    vector<T> B(ts);
    for (size_t i = 0; i < A.size(); i++) {
      if (P[i] != -1) {
        B[P[i]] = A[i];
      }
    }
    st = new ST(B);
  }
  void modify(int p, T val) { st->modify(P[p], val); }
  T query(int x, int y) {
    int tx = Top[x], ty = Top[y];
    if (tx == ty) return Dep[x] <= Dep[y] ? st->query(P[x], P[y] + 1) : query(y, x);
    if (Dep[tx] >= Dep[ty])
      return st->op(st->query(P[tx], P[x] + 1), query(Fa[tx], y));
    else
      return query(y, x);
  }
};
