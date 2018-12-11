#include <bits/stdc++.h>
using namespace std;


template <class T> struct Fenwick2D {
    int n, m;
    vector<vector<T>> V;
    Fenwick2D(int n, int m): n(n), m(m), V(n, vector<T>(m)) {}
    void add(size_t i, size_t j, T x) {
        for (; i < n; i |= i + 1)
            for (int k = j; k < m; k |= k + 1)
                V[i][k] += x;
    }
    T sum(int i, int j) {
        T r = T();
        for (--i, --j; i >= 0; i = (i & (i + 1)) - 1)
            for (int k = j; k >= 0; k = (k & (k + 1)) - 1) r += V[i][k];
        return r;
    }
    T sum(int i, int j, int ii, int jj) {
        return sum(ii, jj) + sum(i, j) - sum(i, jj) - sum(ii, j);
    }
};


int main() {
    int n = 30;
    using B = bitset<6>;
    for (int i = 0; i <= n; i++) {
        cout << i << ' ' << B(i) << ' ' << B(i | (i + 1)) << ' ' << B((i & (i + 1)) - 1) << endl;
    }
    return 0;
}
