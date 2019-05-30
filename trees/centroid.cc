#include <bits/stdc++.h>
using namespace std;

void solve(const vector<vector<int>>& G, int root = 1) {
  vector<char> Use(G.size());
  vector<int> Sz(G.size());
  auto find_c = [&](int root) {
    auto dfs = [&](int u, int p, bool b, auto f) -> int {
      if (!b) Sz[u] = 1;
      for (auto v : G[u])
        if (v != p && !Use[v]) {
          if (!b)
            f(v, u, b, f), Sz[u] += Sz[v];
          else if (Sz[v] * 2 > Sz[root])
            return f(v, u, b, f);
        }
      return u;
    };
    return dfs(root, -1, 0, dfs), dfs(root, -1, 1, dfs);
  };
  auto decompose = [&](int root, auto f) -> void {
    int c = find_c(root);
    Use[c] = 1;
    for (auto u : G[c])
      if (!Use[u]) f(u, f);
    // solve
    Use[c] = 0;
  };
  decompose(root, decompose);
}

int main() {}
