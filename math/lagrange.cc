#include <bits/stdc++.h>
using namespace std;


template <typename T> T lagrange(const vector<T>& X, const vector<T>& Y, T x, T M = T(1e9 + 7)) {
    assert(X.size() == Y.size());
    using LL = long long;
    function<LL(LL)> rev = [&](LL x) { return x == 1 ? 1 : (M - M / x) * rev(M % x) % M; };
    auto sub = [&](LL x, LL y) { return (x - y + M) % M; };
    LL ans = 0;
    for (size_t i = 0; i < X.size(); i++) {
        LL nom = Y[i], dom = 1;
        for (size_t j = 0; j < X.size(); j++) {
            if (j == i) continue;
            nom = nom * sub(x, X[j]) % M;
            dom = dom * sub(X[i], X[j]) % M;
        }
        ans = (ans + nom * rev(dom)) % M;
    }
    return ans;
};


// CF. 995F
using LL = long long;
LL F[3005][3005];
int main() {
    LL n, D;
    cin >> n >> D;
    const int Mod = 1e9 + 7;
    vector<vector<int>> G(n + 1);
    for (int i = 2; i <= n; i++) {
        int x;
        scanf("%d", &x);
        G[x].push_back(i);
    }
    function<void(int)> dfs = [&](int u) {
        for (auto v : G[u]) {
            dfs(v);
        }
        for (int i = 1; i <= min(n, D); i++) {
            LL tmp = 1;
            for (auto v : G[u]) {
                tmp = tmp * F[v][i] % Mod;
            }
            F[u][i] = (F[u][i - 1] + tmp) % Mod;
        }
    };
    dfs(1);
    vector<LL> X;
    for (int i = 0; i <= n; i++) X.push_back(i);
    vector<LL> Y;
    for (int i = 0; i <= n; i++) Y.push_back(F[1][i]);
    cout << lagrange(X, Y, D) << endl;
}
