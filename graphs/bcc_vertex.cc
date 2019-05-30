#include <bits/stdc++.h>
using namespace std;

// {u, v} not split to {u, v} and {v, u}
template <class Edge>
vector<int> bcc_vetex(const vector<Edge>& E, const vector<vector<int>>& G) {
  int n = int(G.size()), m = int(E.size()), ts = 0, t = 0, c = 0;
  vector<int> In(n), L(n), S(m), B(m), C(m);
  auto dfs = [&](int u, auto f) -> void {
    L[u] = In[u] = ++ts;
    for (auto i : G[u]) {
      int v = E[i].u == u ? E[i].v : E[i].u;
      if (!B[i]) S[++t] = i, B[i] = 1;
      if (!In[v]) {
        f(v, f), L[u] = min(L[u], L[v]);
        if (L[v] >= In[u]) {
          ++c;
          do
            C[S[t]] = c;
          while (S[t--] != i);
        }
      } else
        L[u] = min(L[u], In[v]);
    }
  };
  for (int i = 0; i < n; i++)
    if (!In[i]) dfs(i, dfs);
  return C;
}

// CF. 962F
const int N = 1e5 + 5;
int n, m, F[N], Cv[N], Ce[N];
struct Edge {
  int u, v;
};
vector<Edge> E(1);
vector<vector<int>> G(N);
vector<int> S[N];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    G[u].emplace_back(i), G[v].emplace_back(i);
    E.push_back({u, v});
  }
  auto C = bcc_vetex(E, G);
  int mx = *max_element(C.begin(), C.end());
  for (int i = 1; i <= m; i++) {
    Ce[C[i]]++;
    S[C[i]].push_back(E[i].u);
    S[C[i]].push_back(E[i].v);
  }
  for (int i = 1; i <= mx; i++) {
    sort(S[i].begin(), S[i].end());
    S[i].erase(unique(S[i].begin(), S[i].end()), S[i].end());
  }
  for (int i = 1; i <= m; i++)
    if (Ce[C[i]] == (int)S[C[i]].size()) F[i] = 1;
  printf("%d\n", accumulate(F, F + 1 + m, 0));
  for (int i = 1; i <= m; i++)
    if (F[i]) printf("%d ", i);
  puts("");
  return 0;
}
