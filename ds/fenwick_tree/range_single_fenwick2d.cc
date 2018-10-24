#include <bits/stdc++.h>
using namespace std;


template <typename T> struct RSFenwick2D {
    int n, m;
    vector<vector<T>> V;
    RSFenwick2D(int n, int m): n(n), m(m), V(n, vector<T>(m)) {}
    void _add(size_t i, size_t j, T x) {
        for (; i < n; i |= i + 1)
            for (int k = j; k < m; k |= k + 1)
                V[i][k] += x;
    }
    void add(size_t i, size_t j, size_t ii, size_t jj, T x) {
        _add(i, j, x), _add(i, jj, -x), _add(ii, j, -x), _add(ii, jj, x);
    }
    T get(int i, int j) {
        T r = T();
        for (--i, --j; i >= 0; i = (i & (i + 1)) - 1)
            for (int k = j; k >= 0; k = (k & (k + 1)) - 1) r += V[i][k];
        return r;
    }
};

int main() {
    return 0;
}
