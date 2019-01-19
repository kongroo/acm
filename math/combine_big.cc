#include <bits/stdc++.h>
using namespace std;

// Lucas：when m is prime < 1e5，C(n,k)%m = C(n/m,k/m)*C(n%m,k%m)%m

namespace Combine {
using LL = long long;
int inv(LL x, int m) { return x > m ? inv(x % m, m) : x > 1 ? inv(m % x, m) * (m - m / x) % m : x; }
int comod(LL n, LL k, int m = 1e9 + 7) {
    if (k > n) return 0;
    if (k + k > n) return comod(n, n - k, m);
    int num = 1, den = 1;
    for (int i = 1; i <= k; i++) num = num * ((n - i + 1) % m) % m, den = 1LL * den * i % m;
    return 1LL * num * inv(den, m) % m;
}
int lucas(LL n, LL k, int m = 10007) {
    assert(m < 1e5);
    return n || k ? 1LL * lucas(n / m, k / m, m) * comod(n % m, k % m, m) % m : 1;
}
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
