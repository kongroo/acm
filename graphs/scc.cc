#include <bits/stdc++.h>
using namespace std;


// return color array
vector<int> tarjan_scc(const vector<vector<int>> &G) {
    int n = int(G.size()), ts = 0, nscc = 0, tt = 0;
    vector<int> Scc(n, -1), In(n, -1), Low(n, -1), S(n + 1, -1);
    function<void(int)> dfs = [&](int u) {
        In[u] = Low[u] = ts++, S[tt++] = u;
        for (auto v : G[u]) {
            if (In[v] == -1) dfs(v), Low[u] = min(Low[u], Low[v]);
            else if (Scc[v] == -1) Low[u] = min(Low[u], In[v]);
        }
        if (Low[u] == In[u]) {
            while (tt && S[tt] != u) Scc[S[--tt]] = nscc;
            nscc++;
        }
    };
    for (size_t i = 0; i < G.size(); i++) if (In[i] == -1) dfs(i);
    return Scc;
}


int main() {
    return 0;
}
