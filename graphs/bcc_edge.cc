#include <bits/stdc++.h>
using namespace std;


// return Low array as color array
// reverse edge should be update by min(Low[u], In[v]),
// but for edge bcc, it seems ok to use min(Low[u], Low[v])
vector<int> bcc_edge(const vector<vector<int>> &G) {
    int n = int(G.size()), ts = 0, t = 0;
    vector<int> In(n), L(n), S(n + 1);
    auto dfs = [&](int u, int p, auto f) -> void {
        L[u] = In[u] = ++ts, S[t++] = u;
        for (auto v : G[u]) if (v != p) { if (!In[v]) f(v, u, f); L[u] = min(L[u], L[v]); }
        if (In[u] == L[u]) while (t && S[t] != u) L[S[--t]] = L[u];
    };
    for (int i = 0; i < n; i++) if (!In[i]) dfs(i, -1, dfs);
    return L;
}


int main() {
    return 0;
}
