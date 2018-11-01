#include <bits/stdc++.h>
using namespace std;


vector<int> hungary(const vector<vector<int>> &G) {
    vector<int> M(G.size(), -1);
    vector<char> B(G.size(), 0);
    function<bool(int, int)> dfs = [&](int u, int p) -> bool {
        B[u] = 1;
        if (M[u] < 0 && p != -1) return true;
        if (M[u] >= 0 && M[u] != p) return dfs(M[u], u);
        for (auto v : G[u]) if (v != p && !B[v] && dfs(v, u))
                return M[u] = v, M[v] = u, 1;
        return 0;
    };
    for (size_t i = 0; i < G.size(); ++i)
        if (M[i] < 0) fill(B.begin(), B.end(), 0), dfs(i, -1);
    return M;
}


int main() {
    return 0;
}
