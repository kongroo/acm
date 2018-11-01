#include <bits/stdc++.h>
using namespace std;

/*
 * C(n, k) = C(n-1, k) + C(n-1, k-1), C(n, k) = C(n, k-1) * (n-k+1) / k
 * C(n, 0) + C(n, 1) + ... + C(n, n) = 2^n
 * C(n, 1) + ... = C(n, 0) + ... = 2^(n-1)
 * C(n, 0)^2 + ... + C(n, n)^2 = C(2*n, n)
 * Lucas：when m is prime < 1e5，C(n,k)%m = C(n/m,k/m)*C(n%m,k%m)%m
*/

struct Combine {
    using LL = long long;
    static constexpr int inv(LL x, int m) {
        return x > m ? inv(x % m, m) : x > 1 ? inv(m % x, m) * (m - m / x) % m : x;
    }
    static constexpr int comod(LL n, LL k, int m = 1e9 + 7) {
        if (k + k > n) return comod(n, n - k, m);
        int num = 1, den = 1;
        for (int i = 1; i <= k; i++) num = num * ((n - i + 1) % m) % m, den = 1LL * den * i % m;
        return 1LL * num * inv(den, m) % m;
    }
    static constexpr int lucas(LL n, LL k, int m = 10007) {
        assert(m < 1e5);
        return n || k ? 1LL * lucas(n / m, k / m, m) * comod(n % m, k % m, m) % m : 1;
    }
    int m;
    vector<LL> F;
    Combine(int n, int m) : m(m), F(n, 1) { for (int i = 1; i < n; i++) F[i] = F[i - 1] * i % m; }
    int com(LL n, LL k) { return F.at(n) * inv(F.at(n - k) * F[k], m) % m; }
    int per(LL n, LL k) { return F.at(n) * inv(F.at(k), m) % m; }
};


// 51Nod. 1269
int main() {
    using LL = long long;
    const int Mod = 1e9 + 7;
    int n;
    scanf("%d", &n);
    LL k, ans = 0;
    scanf("%lld", &k);
    vector<LL> S(n);
    for (int i = 0; i < n; i++) scanf("%lld", &S[i]);
    for (int s = 0; s < (1 << n); s++) {
        bool flag = __builtin_popcount(s) & 1;
        LL t = k;
        for (int i = 0; i < n; i++) if (1 << i & s) t -= S[i] + 1;
        if (t < 0) continue;
        ans += (flag ? -1 : 1) * Combine::comod(t + n - 1, n - 1, Mod);
        ans = (ans + Mod) % Mod;
    }
    printf("%lld\n", ans);
    return 0;
}
