#include <bits/stdc++.h>
using namespace std;


// Tarjan算法求无向图的边双联通分量，返回Low数组，
// 同一个双联通分量中的点Low值相等。
// 反向边应该用min(Low[u], In[v])更新，
// 但对于边双联通分量，似乎也可以用min(Low[u], Low[v])更新。
vector<int> tarjan_bcc(const vector<vector<int>>& G) {
    int n = int(G.size()), ts = 0, tt = 0;
    vector<int> In(n, -1), Low(n, -1), S(n + 1, -1);
    function<void(int, int)> dfs = [&](int u, int p) {
        Low[u] = In[u] = ts++;
        S[tt++] = u;
        for (auto v : G[u]) if (v != p) {
                if (In[v] == -1) dfs(v, u);
                Low[u] = min(Low[u], Low[v]);
            }
        if (In[u] == Low[u]) while (tt && S[tt] != u) Low[S[--tt]] = Low[u];
    };
    for (int i = 0; i < n; i++) if (In[i] == -1) dfs(i, -1);
    return Low;
}
