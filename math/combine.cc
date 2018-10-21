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
    static constexpr LL inv(LL x, LL m) {
        return x > m ? inv(x % m, m) : x > 1 ? inv(m % x, m) * (m - m / x) % m : x;
    }
    static constexpr LL comod(LL n, LL k, LL m = 1e9 + 7) {
        if (k + k > n) return comod(n, n - k, m);
        LL num = 1, den = 1;
        for (int i = 1; i <= k; i++)  num = num * (n - i + 1) % m, den = den * i % m;
        return num * inv(den, m) % m;
    }
    static const int lucas(int n, int k, int m = 10007) {
        return assert(m < 1e5), n || k ? lucas(n / m, k / m, m) * comod(n % m, k % m, m) % m : 1;
    }
    LL m;
    vector<LL> F;
    Combine(int n, LL mod) : m(mod), F(n + 1, 1) {
        for (int i = 1; i <= n; i++) F[i] = F[i - 1] * i % m;
    }
    LL com(LL n, LL k) { return F.at(n) * inv(F.at(n - k) * F[k], m) % m; }
    LL per(LL n, LL k) { return F.at(n) * inv(F.at(k), m) % m; }
};


int main() {
    return 0;
}
