#include <bits/stdc++.h>
using namespace std;


struct Lagrange {
    using LL = long long;
    int n, m;
    vector<LL> Inv, Den;
    Lagrange(int n, int m): n(n), m(m), Inv(n, 1), Den(n, 1) {
        assert(n > 1);
        for (int i = 2; i < n; i++)
            Inv[i] = (m - m / i) * Inv[m % i] % m, Den[i] = Den[i - 1] * Inv[i] % m;
    }
    constexpr LL inv(LL x) { return x < 2 ? x : (m - m / x) * inv(m % x) % m; }
    constexpr LL sub(LL x, LL y) { return (x - y + m) % m; }
    constexpr LL add(LL x, LL y) { return (x + y) % m; }
    // O(k^2), naive
    template <typename T> LL interp(const vector<T> &X, const vector<T> &Y, LL x) {
        LL ans = 0;
        for (size_t i = 0; i < X.size(); i++) {
            LL num = Y.at(i), den = 1;
            for (size_t j = 0; j < X.size(); j++) if (j != i)
                    num = num * sub(x, X[j]) % m, den = den * sub(X[i], X[j]) % m;
            ans = (ans + num * inv(den)) % m;
        }
        return ans;
    }
    // O(k), for X is [0, 1, ..., k]
    template <typename T> LL interp_fast(const vector<T> &Y, LL x) {
        int k = (int)Y.size() - 1;
        assert(k < n);
        if (x <= k) return Y[x];
        vector<LL> Suf(1, 1);
        for (LL j = k, tmp = 1; j > 0; j--) Suf.push_back(tmp = tmp * sub(x, j) % m);
        LL ans = 0, den = Den[k];
        for (LL j = 0, pref = 1; j <= k; j++) {
            LL num = pref * Suf.back() % m;
            pref = pref * sub(x, j) % m, Suf.pop_back();
            LL t = num * den % m * Y[j] % m;
            ans = (k - j) & 1 ? sub(ans, t) : add(ans, t);
            if (j < k) den = den * Inv[j + 1] % m * (k - j) % m;
        }
        return ans;
    }
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
    vector<LL> Y;
    for (int i = 0; i <= n; i++) Y.push_back(F[1][i]);
    Lagrange lg(n + 1, Mod);
    cout << lg.interp_fast(Y, D) << endl;
}
