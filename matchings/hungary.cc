#include <bits/stdc++.h>
using namespace std;


vector<int> hungary(const vector<vector<int>>& G) {
    vector<int> Match(G.size(), -1);
    vector<char> Vis(G.size(), 0);
    function<bool(int, int)> dfs = [&](int u, int p) -> bool {
        Vis[u] = 1;
        if (Match[u] < 0 && p != -1) return true;
        if (Match[u] >= 0 && Match[u] != p) return dfs(Match[u], u);
        for (auto v : G[u]) {
            if (v == p || Vis[v]) continue;
            if (dfs(v, u)) {
                Match[u] = v;
                Match[v] = u;
                return true;
            }
        }
        return false;
    };
    for (size_t i = 0; i < G.size(); ++i) {
        fill(Vis.begin(), Vis.end(), 0);
        if (Match[i] < 0) dfs(i, -1);
    }
    return Match;
}

int main() {
    return 0;
}
