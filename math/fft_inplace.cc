#include <bits/stdc++.h>
using namespace std;


template <typename T> void fft_inplace(vector<complex<T>>& A, int inv) {
    assert(inv == 1 || inv == -1);
    const T PI = acos(-1.0);
    static vector<int> rev;
    auto& R = A;
    R.resize(1 << (32 - __builtin_clz((int)R.size() - 1)));
    int n = (int)R.size();
    int m = 31 - __builtin_clz(n);
    if ((int)rev.size() != n) {
        rev.resize(n);
        for (int i = 1; i < n; i++)
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (m - 1));
    }
    for (int i = 0; i < n; i++) if (i < rev[i]) swap(R[i], R[rev[i]]);
    for (int l = 1; l <= n; l <<= 1) {
        complex<T> wl(cos(inv * 2 * PI / l), sin(inv * 2 * PI / l));
        for (int s = 0; s < n; s += l) {
            complex<T> w(1, 0);
            for (int i = 0; i < (l >> 1); i++) {
                complex<T> u = R[s + i];
                complex<T> t = w * R[s + i + (l >> 1)];
                R[s + i] = u + t;
                R[s + i + (l >> 1)] = u - t;
                w *= wl;
            }
        }
    }
    if (inv == -1) for (int i = 0; i < n; i++) R[i] /= n;
}


int main() {
    return 0;
}
