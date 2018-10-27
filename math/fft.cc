#include <bits/stdc++.h>
using namespace std;


namespace FFT {
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
    assert((inv == 1 || inv == -1) && (is_same<T, double>::value || is_same<T, long double>::value));
    int n = 1 << (32 - __builtin_clz(A.size() - 1));
    A.resize(n), arrange(A);
    for (int l = 1; l < n; l <<= 1) {
        complex<T> wl(cos(inv * PI / l), sin(inv * PI / l)), w(1, 0), t;
        for (int i = 0; i < l; i++, w *= wl)
            for (int s = 0; s < n; s += l + l)
                t = w * A[s + i + l], A[s + i + l] = A[s + i] - t, A[s + i] += t;
    }
    if (inv == -1) for (int i = 0; i < n; i++) A[i] /= n;
}
template <typename T> vector<T> multiply(const vector<T> &A, const vector<T> &B) {
    bool flag = is_same<T, double>::value || is_same<T, long double>::value;
    double bias = flag ? 0 : 0.5;
    int s = A.size() + B.size() - 1;
    vector<complex<double>> U, V; // or long double
    for (auto x : A) U.emplace_back(x, 0);
    for (auto x : B) V.emplace_back(x, 0);
    U.resize(s), V.resize(s), fourier(U, 1), fourier(V, 1);
    for (size_t i = 0; i < U.size(); i++) U[i] *= V[i];
    fourier(U, -1);
    vector<T> R;
    for (int i = 0; i < s; i++) R.push_back(U[i].real() + bias);
    return R;
}
};


// 51Nod. 1028
int main() {
    char s[100005], t[100005];
    scanf("%s%s", s, t);
    int n = strlen(s), m = strlen(t);
    vector<int> A, B;
    for (int i = n - 1; i >= 0; i--) A.push_back(s[i] - '0');
    for (int i = m - 1; i >= 0; i--) B.push_back(t[i] - '0');
    auto R = FFT::multiply(A, B);
    for (size_t i = 0; i < R.size(); i++) {
        if (R[i] >= 10) {
            if (i + 1u == R.size()) R.push_back(0);
            R[i + 1] += R[i] / 10;
            R[i] %= 10;
        }
    }
    reverse(R.begin(), R.end());
    for (auto c : R) printf("%d", c);
    puts("");
    return 0;
}
