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
};


// Luogu. 4245
int main() {
    int n, m, p;
    scanf("%d%d%d", &n, &m, &p);
    n++, m++;
    vector<int> P(n), Q(m);
    for (int i = 0; i < n; i++) scanf("%d", &P[i]);
    for (int i = 0; i < m; i++) scanf("%d", &Q[i]);
    auto R = MFFT::multiply(P, Q, p);
    for (size_t i = 0; i < R.size(); i++) printf("%d%c", R[i], " \n"[i + 1 == R.size()]);
    return 0;
}
