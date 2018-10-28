#include <bits/stdc++.h>
using namespace std;


namespace MFFT {
static const double PI = acos(-1.0);
template <typename T> void arrange(vector<T> &A) {
    int n = A.size();
    assert(n == (n & -n));
    for (int i = 1, x = 0, y = 0; i <= n; i++) {
        if (x > y) swap(A[x], A[y]);
        x ^= i & -i, y ^= n / (i & -i) >> 1;
    }
}
template <typename T> void fourier(vector<complex<T>> &A, int inv) {
    assert((inv == 1 || inv == -1) && is_floating_point<T>::value);
    int n = 1 << (32 - __builtin_clz(A.size() - 1));
    A.resize(n), arrange(A);
    vector<complex<T>> W(n >> 1, {1, 0});
    for (int l = 1; l < n; l <<= 1) {
        complex<T> wl(cos(inv * PI / l), sin(inv * PI / l)), t;
        for (int i = l - 2; i >= 0; i -= 2) W[i] = W[i >> 1];
        for (int i = 1; i < l; i += 2) W[i] = W[i - 1] * wl;
        for (int i = 0; i < l; i++)
            for (int s = 0; s < n; s += l + l)
                t = W[i] * A[s + i + l], A[s + i + l] = A[s + i] - t, A[s + i] += t;
    }
    if (inv == -1) for (int i = 0; i < n; i++) A[i] /= n;
}
template <typename T> vector<T> multiply(const vector<T> &A, const vector<T> &B, int p = 1e9 + 7) {
    assert(is_integral<T>::value);
    using CD = complex<double>; // or long double;
    using LL = long long;
    int s = A.size() + B.size() - 1;
    vector<CD> U, V;
    for (auto x : A) U.emplace_back(x >> 15, x & 32767);
    for (auto x : B) V.emplace_back(x >> 15, x & 32767);
    U.resize(s), V.resize(s), fourier(U, 1), fourier(V, 1);
    for (size_t i = 0, n = U.size(); i + i <= n; i++) {
        size_t j = (n - i) & (n - 1);
        auto a = U[i], b = U[j], c = V[i], d = V[j];
        U[i] = (a + conj(b)) * (c + conj(d)) * 0.25 - (a - conj(b)) * (c - conj(d)) * CD(0, 0.25);
        U[j] = (b + conj(a)) * (d + conj(c)) * 0.25 - (b - conj(a)) * (d - conj(c)) * CD(0, 0.25);
        V[i] = CD(0, 0.5) * (conj(b * d) - a * c), V[j] = CD(0, 0.5) * (conj(a * c) - b * d);
    }
    fourier(U, -1), fourier(V, -1);
    vector<T> R(s);
    for (int i = 0; i < s; i++) {
        LL t1 = (LL)(U[i].real() + 0.5) % p;
        LL t2 = (LL)(V[i].real() + 0.5) % p;
        LL t3 = (LL)(U[i].imag() + 0.5) % p;
        R[i] = ((t1 << 30) % p + (t2 << 15) % p + t3) % p;
    }
    return R;
}
int mpow(long long a, int k, int m) { int r(1); for (a %= m; k; k >>= 1, a = a * a % m) if (k & 1)r = r * a % m; return r; }
template <typename T> vector<T> inv(const vector<T> &A, int n, int p) {
    assert(is_integral<T>::value && A[0]);
    vector<T> R;
    function<void(int)> inv_ = [&](int n) {
        if (n == 1) return R = {mpow(A[0], p - 2, p)}, void();
        inv_((n + 1) >> 1);
        auto Tmp = multiply(A, R, p);
        Tmp[0] = (2 - Tmp[0] + p) % p;
        for (size_t i = 1; i < Tmp.size(); i++) Tmp[i] = Tmp[i] ? p - Tmp[i] : 0;
        R = multiply(R, Tmp, p);
        R.resize(n);
    };
    inv_(n);
    return R;
}
};


// 51Nod. 1228
using LL = long long;
LL inv(LL x, LL m) { return x > m ? inv(x % m, m) : x > 1 ? inv(m % x, m) * (m - m / x) % m : x; }
LL mpow(LL a, LL k, LL m) { LL r(1); for (a %= m; k; k >>= 1, a = a * a % m) if (k & 1)r = r * a % m; return r; }

vector<int> bernouli_n(int n, int m = 1e9 + 7) {
    vector<int> A;
    for (int i = 0, tmp = 1; i < n; i++) {
        tmp = 1LL * tmp * (i + 1) % m;
        A.push_back(inv(tmp, m));
    }
    auto B = MFFT::inv(A, n, m);
    for (int i = 1, tmp = 1; i < n; i++) {
        tmp = 1LL * tmp * i % m;
        B[i] = 1LL * B[i] * tmp % m;
    }
    B[1] = inv(2, m);
    return B;
}

auto B = bernouli_n(50001);
int main() {
    using LL = long long;
    const int Mod = 1e9 + 7;
    vector<int> Inv(50002, 1);
    for (int i = 2; i <= 50001; i++) Inv[i] = 1LL * (Mod - Mod / i) * Inv[Mod % i] % Mod;
    int t;
    scanf("%d", &t);
    while (t--) {
        LL n, k;
        scanf("%lld%lld", &n, &k);
        LL ans = 0, tmp1 = mpow(n, k + 1, Mod), tmp2 = 1, invn = inv(n, Mod);
        for (int i = 0; i <= k; i++) {
            ans += B[i] * tmp1 % Mod * tmp2 % Mod;
            tmp1 = tmp1 * invn % Mod;
            tmp2 = tmp2 * (k + 1 - i) % Mod * Inv[i + 1] % Mod;
            ans %= Mod;
        }
        ans = ans * inv(k + 1, Mod) % Mod;
        printf("%lld\n", ans);
    }
    return 0;
}
