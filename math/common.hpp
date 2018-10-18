#include <bits/stdc++.h>
using namespace std;


// 计算a的k次方模m，k>=0
int pow(long long a, long long k, int m = int(1e9 + 7)) {
    int s = 1 % m;
    for (a = a % m; k; a = a * a % m, k >>= 1) if (k & 1) s = s * a % m;
    return s;
}


// 计算n的欧拉函数值
int phi(int n) {
    int m = n;
    for (int i = 2; i <= n; i++) if (n % i == 0)
            for (m = m / i * (i - 1); n % i == 0; n /= i);
    if (n > 1) m = m / n * (n - 1);
    return m;
}


// 计算x在模m下的乘法逆元，须保证gcd(x,m)==1
int inv(int x, int m = int(1e9 + 7)) {
    return x > 1 ? inv(m % x, m) * 1LL * (m - m / x) % m : x;
}


// 计算对于素数m，[1, m)的乘法逆元
vector<int> inv_n(int n, int m = int(1e9 + 7)) {
    vector<int> Inv(n);
    Inv[1] = 1;
    for (int x = 2; x < n; x++) Inv[x] = Inv[m % x] * 1LL * (m - m / x) % m;
    return Inv;
}


// 计算第n个斐波那契数，返回第n和第n-1个斐波那契数模m的值
// 其中n必须为非负整数，F[0]=0, F[1]=1
pair<int, int> fib(long long n, int m = int(1e9 + 7)) {
    if (n <= 1) return make_pair(n, 0);
    auto t = fib(n / 2, m);
    int x = t.first, y = t.second;
    int p = (1LL * x * x + 1LL * y * y) % m;
    int q = 1LL * x * (x + 2LL * y) % m;
    if (n & 1) return make_pair((0LL + p + q) % m, q);
    return make_pair(q, p);
}
/* 斐波那契数列性质:
 * 奇数项求和: F[1]+F[3]+...+F[2n-1] = F[2n]-F[2]+F[1]
 * 偶数项求和: F[2]+F[4]+...+F[2n] = F[2n+1]-F[1]
 * 平方求和: F[1]^2+F[2]^2+...+F[n]^2 = F[n]F[n+1]
 * F[2n] = F[n](F[n-1]+F[n+1])
 * F[2n-1] = F[n]^2 + F[n-1]^2
*/


// 计算组合数C(n, k) % m, C(n, k) = n!/[k!(n-k)!]
int comod(int n, int k, int m = int(1e9 + 7)) {
    if (k + k > n) return comod(n, n - k, m);
    function<int(int)> inv = [&](int x) { return x > 1 ? inv(m % x) * 1LL * (m - m / x) % m : x; };
    int num = 1, den = 1;
    for (int i = 1; i <= k; i++) {
        num = 1LL * num * (n - i + 1) % m;
        den = 1LL * den * i % m;
    }
    return 1LL * num * inv(den) % m;
}


int lucas(int n, int k, int m = 10007) {
    assert(m < int(1e5));
    if (n == 0 && k == 0) return 1;
    return 1LL * lucas(n / m, k / m, m) * comod(n % m, k % m, m) % m;
}

/* 组合数性质:
 * 递推公式：C(n, k) = C(n-1, k) + C(n-1, k-1), C(n, k) = C(n, k-1) * (n-k+1) / k
 * 二项式定理：C(n, 0) + C(n, 1) + ... + C(n, n) = 2^n
 * C(n, 1) + ... = C(n, 0) + ... = 2^(n-1)
 * C(n, 0)^2 + ... + C(n, n)^2 = C(2*n, n)
 * Lucas定理：当m是小于1e5的素数时，C(n,k)%m = C(n/m,k/m)*C(n%m,k%m)%m
*/

// 加速多次组合数计算
namespace Combine {
using LL = long long;
LL m;
vector<LL> F;
void init(int n, LL mod) {
    m = mod;
    F.resize(n + 1);
    F[0] = 1;
    for (int i = 1; i <= n; i++) F[i] = F[i - 1] * i % m;
}
LL inv(LL x) { return x > 1 ? inv(m % x) * (m - m / x) % m : x; }
LL com(LL n, LL k) { return F[n] * inv(F[n - k] * F[k] % m) % m; }
LL per(LL n, LL k) { return F[n] * inv(F[k]) % m; }
}
