#include <bits/stdc++.h>
using namespace std;


template <typename T> constexpr auto bkdr_hash(const T& S) {
    auto res1 = 0ULL, res2 = 0ULL, seed1 = 131ULL, seed2 = 1313ULL;
    for (auto c : S) res1 = res1 * seed1 + c, res2 = res2 * seed2 + c;
    return res1 * res2;
}


// CF. 154C
int main() {
    using ULL = unsigned long long;
    using PII = pair<int, int>;
    int n, m;
    scanf("%d%d", &n, &m);
    vector<vector<int>> G(n + 1);
    vector<PII> E;
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
        E.emplace_back(u, v);
    }
    for (int i = 1; i <= n; i++) {
        sort(G[i].begin(), G[i].end());
    }
    unordered_map<ULL, int>  M;
    for (int i = 1; i <= n; i++) M[bkdr_hash(G[i])]++;
    auto ans = 0LL;
    for (auto p : M) {
        int t = p.second;
        ans += 1LL * t * (t - 1) / 2;
    }
    for (auto p : E) {
        int u, v;
        tie(u, v) = p;
        if (!binary_search(G[u].begin(), G[u].end(), u))
            G[u].push_back(u), sort(G[u].begin(), G[u].end());
        if (!binary_search(G[v].begin(), G[v].end(), v))
            G[v].push_back(v), sort(G[v].begin(), G[v].end());
        if (G[u] == G[v]) ans++;
    }
    printf("%lld\n", ans);
    return 0;
}
