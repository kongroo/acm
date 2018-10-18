#include <bits/stdc++.h>
using namespace std;


// if A[i][j] has value, A[i+1][j] and A[i][j+1]
// must be null or greater than A[i][j]
// F[1] = 1, F[2] = 2, F[n] = F[n-1] + (n-1) * F[n-2]
// hook formula: given shape, F[n] = n! / product of all hook length,
// hook length = itself + right and down cells



// 51Nod. 1129
#define DEBUG(x) cerr << #x << ": " << (x) << endl;
using LL = long long ;
LL mpow(LL a, LL k, LL m) { LL r(1); for (a %= m; k; k >>= 1, a = a * a % m) if (k & 1)r = r * a % m; return r; }
vector<int> inv_n(int n, int m = int(1e9 + 7)) {
    vector<int> Inv(n);
    Inv[1] = 1;
    for (int x = 2; x < n; x++) Inv[x] = Inv[m % x] * 1LL * (m - m / x) % m;
    return Inv;
}
const int Mod = 10007;
const auto Inv = inv_n(Mod, Mod);
pair<int, int> factorial(int n) {
    static vector<int> Cycle;
    if (Cycle.empty()) {
        Cycle.resize(Mod);
        Cycle[0] = 1;
        for (int i = 1; i < Mod; i++) Cycle[i] = Cycle[i - 1] * i % Mod;
    }
    int q = n / Mod;
    int x = mpow(Cycle.back(), q, Mod) * Cycle[n % Mod] % Mod, y = q;
    if (q) {
        auto p = factorial(q);
        x = x * p.first % Mod;
        y += p.second;
    }
    return {x, y};
}

int calc(int n, int m) {
    assert(n <= m);
    auto num = factorial(n * m);
    auto den = 1LL, mod0 = 0LL;
    mod0 += num.second;
    for (int i = 1; i < n; i++) {
        if (i % Mod == 0) {
            mod0 -= i;
            den = den * mpow(i / Mod, i, Mod) % Mod;
        } else den = den * mpow(i, i, Mod) % Mod;
        int j = n + m - i;
        if (j % Mod == 0) {
            mod0 -= i;
            den = den * mpow(j / Mod, i, Mod) % Mod;
        } else den = den * mpow(j, i, Mod) % Mod;
    }
    auto p1 = factorial(m), p2 = factorial(n - 1);
    int x = p1.first * Inv[p2.first] % Mod, y = p1.second - p2.second;
    den = den * mpow(x, n, Mod) % Mod;
    mod0 -= y * n;
    if (mod0 != 0) return 0;
    return num.first * Inv[den] % Mod;
}

int main() {
    int N;
    scanf("%d", &N);
    int ans = 0;
    for (int n = 1; n * n <= N; n++) {
        if (N % n) continue;
        int m = N / n, tmp = calc(n, m);
        ans += tmp;
        if (m != n) ans += tmp;
        ans %= Mod;
    }
    printf("%d\n", ans);
    return 0;
}
