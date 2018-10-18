#include <bits/stdc++.h>
using namespace std;


vector<int> hopcroft_karp(const vector<vector<int>>& G) {
    // todo
    size_t n = G.size();
    vector<int> Match(n, -1);
    vector<int> Dist(n, -1);
    auto bfs = [&]() {
        queue<int> Q;
        for (size_t i = 0; i < n; i++) if (Match[i] == -1);
        while (!Q.empty()) {
            u = Q.front();
            Q.pop();
            for (auto v : G[u]) {
                if (Dist[Match[v]] == INF) {
                    Dist[Match[v]] = Dist[u] + 1;
                    Q.push(Match[v]);
                }
            }
        }
    };
    function<bool(int, int)> dfs = [&](int u, int p) {
    };
    while (bfs()) for (size_t i = 0; i < G.size(); i++) if (Match[i] == -1) dfs(i);
    return Match;
}

int main() {
    return 0;
}
