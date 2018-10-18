#include <bits/stdc++.h>
using namespace std;


// Tarjan算法求有向图的全联通分量，
// 返回每个节点的染色数组，树值相同则在同一个分量中。
vector<int> tarjan_scc(const vector<vector<int>>& G) {
    int n = int(G.size()), ts = 0, nscc = 0, tt = 0;
    vector<int> Scc(n, -1), In(n, -1), Low(n, -1), S(n + 1, -1);
    function<void(int)> dfs = [&](int u) {
        In[u] = Low[u] = ts++;
        S[tt++] = u;
        for (auto v : G[u]) {
            if (In[v] == -1) {
                dfs(v);
                Low[u] = min(Low[u], Low[v]);
            } else if (Scc[v] == -1) Low[u] = min(Low[u], In[v]);
        }
        if (Low[u] == In[u]) {
            while (tt && S[tt] != u) Scc[S[--tt]] = nscc;
            nscc++;
        }
    };
    for (size_t i = 0; i < G.size(); i++) if (In[i] == -1) dfs(i);
    return Scc;
}
