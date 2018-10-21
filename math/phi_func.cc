#include <bits/stdc++.h>
using namespace std;

// a ^ phi(m) % m = 1, euler's theorem
// a ^ (m-1) % m = 1, if gcd(a, m) = 1, fermat's little theorem
// a ^ n % m = a ^ (n % phi(m)) % m, if gcd(a, m) = 1
// a ^ n % m = a ^ (phi(m) + n % phi(m)) % m, if n >= log2(m) [or n >= phi(m)]
constexpr long long phi(long long n) {
    auto ret = n;
    for (auto i = 2LL; i * i <= n; i++)
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            ret -= ret / i;
        }
    return n > 1 ? ret - ret / n : ret;
}



// CF. 906D
using LL = long long;
auto Mod = [](LL x, LL m) { return x < m ? x : x % m + m; };
LL powmod(LL a, LL k, LL m) { LL res = 1; for (a = Mod(a, m); k; k >>= 1, a = Mod(a * a, m)) if (k & 1)res = Mod(res * a, m); return res; }
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> A(n + 1);
    for (int i = 1; i <= n; i++) scanf("%d", &A[i]);
    int q;
    scanf("%d", &q);
    auto getPhi = [&](int n) {
        static unordered_map<int, int> M;
        if (M.count(n)) return M[n];
        return M[n] = phi(n);
    };
    function<int(int, int, int)> calc = [&](int l, int r, int m) {
        if (l == r || m == 1) return (int)Mod(A[l], m);
        return (int)powmod(A[l], calc(l + 1, r, getPhi(m)), m);
    };
    while (q--) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", calc(l, r, m) % m);
    }
    return 0;
}
