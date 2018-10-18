#include <bits/stdc++.h>
using namespace std;


namespace HashW {
using ULL = unsigned long long;
vector<ULL> P;
void init(int n) {
    P.assign(n + 1, 1313131313ULL);
    for (int i = 1; i <= n; i++) P[i] *= P[i - 1];
}
template <typename T> ULL get(const T& S) {
    ULL ret = 0;
    for (auto c : S) ret += P[c];
    return ret;
}
}


// CF. 154C
int main() {
    using ULL = unsigned long long;
    using PII = pair<int, int>;
    int n, m;
    scanf("%d%d", &n, &m);
    HashW::init(n);
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
    for (int i = 1; i <= n; i++) M[HashW::get(G[i])]++;
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
