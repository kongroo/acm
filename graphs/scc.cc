#include <bits/stdc++.h>
using namespace std;

// return color array
vector<int> tarjan_scc(const vector<vector<int>>& G) {
  int n = int(G.size()), ts = 0, nc = 0, t = 0;
  vector<int> C(n, -1), In(n), L(n), S(n + 1, -1);
  auto dfs = [&](int u, auto f) -> void {
    In[u] = L[u] = ++ts, S[t++] = u;
    for (auto v : G[u]) {
      if (!In[v]) f(v, f), L[u] = min(L[u], L[v]);
      else if (C[v] < 0) L[u] = min(L[u], In[v]);
    }
    if (L[u] == In[u]) { while (t && S[t] != u) C[S[--t]] = nc; nc++; }
  };
  for (size_t i = 0; i < G.size(); i++) if (!In[i]) dfs(i, dfs);
  return C;
}

int main() { return 0; }
