#include <bits/stdc++.h>
using namespace std;


template <typename T> struct RangeFenwick2D {
    int n, m;
    vector<vector<T>> V[4];
    RangeFenwick2D(int n, int m): n(n), m(m) { for (int i = 0; i < 4; i++) V[i].assign(n, vector<T>(m)); }

    void _add(size_t i0, size_t j0, T x) {
        for (int i = i0; i < n; i |= i + 1)
            for (int j = j0; j < m; j |= j + 1)
                V[0][i][j] += x, V[1][i][j] -= x * i0, V[2][i][j] -= x * j0, V[3][i][j] += x * i0 * j0;
    }
    void add(size_t i, size_t j, size_t ii, size_t jj, T x) {
        _add(i, j, x), _add(i, jj, -x), _add(ii, j, -x), _add(ii, jj, x);
    }
    T sum(int i0, int j0) {
        T r = T();
        for (int i = i0 - 1; i >= 0; i = (i & (i + 1)) - 1)
            for (int j = j0 - 1; j >= 0; j = (j & (j + 1)) - 1)
                r += V[0][i][j] * i0 * j0 + V[3][i][j] + j0 * V[1][i][j] + i0 * V[2][i][j];
        return r;
    }
    T sum(int i, int j, int ii, int jj) { return sum(i, j) + sum(ii, jj) - sum(i, jj) - sum(ii, j); }
};


// 51Nod. 1210
int main() {
    using LL = long long;
    int n, m, q;
    scanf("%d%d%d", &m, &n, &q);
    RangeFenwick2D<LL> fw(n + 1, n + 1);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
            int x;
            scanf("%d", &x);
            fw.add(i, j, i + 1, j + 1, x);
        }
    while (q--) {
        int x1, x2, y1, y2, z, a;
        scanf("%d%d%d%d%d%d", &y1, &x1, &y2, &x2, &z, &a);
        LL tot = fw.sum(x1, y1, x2 + 1, y2 + 1);
        LL cnt = (x2 - x1 + 1) * (y2 - y1 + 1);
        if (tot < z * cnt) fw.add(x1, y1, x2 + 1, y2 + 1, a);
    }
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++)
            printf("%lld%c", fw.sum(i, j, i + 1, j + 1), " \n"[j == m]);
    return 0;
}
