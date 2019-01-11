#include <bits/stdc++.h>
using namespace std;


vector<vector<int>> get_dominator_tree(const vector<vector<int>> &G, int root) {
    int n = (int)G.size(), sz = 0;
    vector<int> In(n, -1), A(n), Idom(n), Semi(n), B(n), Fa(n), Pa(n);
    vector<vector<int>> Dom(n), rG(n), Ret(n);
    auto dfs = [&](int u, auto f) -> void {
        In[u] = sz, A[sz++] = Fa[u] = B[u] = Semi[u] = u;
        for (auto v : G[u]) if (rG[v].push_back(u), !~In[v]) f(v, f), Pa[In[v]] = In[u];
    };
    dfs(root, dfs);
    auto get = [&](int x, auto f) -> int {
        if (x == Fa[x]) return x;
        int y = f(Fa[x], f);
        if (Semi[B[Fa[x]]] < Semi[B[x]]) B[x] = B[Fa[x]];
        return Fa[x] = y;
    };
    for (int i = sz - 1, u, v; u = A[i], i > 0; --i) {
        for (auto rv : rG[u]) if (~(v = In[rv]))
                get(v, get), Semi[i] = min(Semi[i], Semi[B[v]]);
        Dom[Semi[i]].push_back(i);
        int x = Fa[i] = Pa[i];
        for (auto z : Dom[x]) get(z, get), Idom[z] = Semi[B[z]] < x ? B[z] : x;
        Dom[x].clear();
    }
    for (int i = 1; i < sz; i++) {
        if (Semi[i] != Idom[i]) Idom[i] = Idom[Idom[i]];
        Dom[Idom[i]].push_back(i);
    }
    for (int u = 0; u < n; u++) for (auto v : Dom[u]) Ret[A[u]].push_back(A[v]);
    return Ret;
}


// Luogu. 5180
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<vector<int>> G(n + 1);
    while (m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
    }
    auto R = get_dominator_tree(G, 1);
    vector<int> F(n + 1);
    auto dfs = [&](int u, int p, auto f) -> void {
        F[u] = 1;
        for (auto v : R[u]) if (v != p)
                f(v, u, f), F[u] += F[v];
    };
    dfs(1, 0, dfs);
    for (int i = 1; i <= n; i++) printf("%d%c", F[i], " \n"[i == n]);
}
