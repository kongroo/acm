#include <bits/stdc++.h>
using namespace std;


// return Low array as color array
// reverse edge should be update with min(Low[u], In[v]),
// but for edge bcc, it seems ok to use min(Low[u], Low[v])
vector<int> tarjan_bcc(const vector<vector<int>> &G) {
    int n = int(G.size()), ts = 0, tt = 0;
    vector<int> In(n, -1), Low(n, -1), S(n + 1, -1);
    function<void(int, int)> dfs = [&](int u, int p) {
        Low[u] = In[u] = ts++, S[tt++] = u;
        for (auto v : G[u]) if (v != p) {
                if (In[v] == -1) dfs(v, u);
                Low[u] = min(Low[u], Low[v]);
            }
        if (In[u] == Low[u]) while (tt && S[tt] != u) Low[S[--tt]] = Low[u];
    };
    for (int i = 0; i < n; i++) if (In[i] == -1) dfs(i, -1);
    return Low;
}


int main() {
    return 0;
}
