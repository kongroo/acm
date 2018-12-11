#include <bits/stdc++.h>
using namespace std;


template <class T> struct RangeFenwick {
    vector<T> V[2];
    RangeFenwick(int n) { for (int i = 0; i < 2; i++) V[i].assign(n, T()); }
    void _add(size_t i, T x, int k) { for (; i < V[k].size(); i |= i + 1) V[k][i] += x; }
    void add(int l, int r, T x) { _add(l, x, 0); _add(r, -x, 0); _add(l, -x * l, 1); _add(r, x * r, 1); }
    T _sum(int i, int k) { T r = T(); for (--i; i >= 0; i = (i & (i + 1)) - 1) r += V[k][i]; return r; }
    T sum(int i) { return i * _sum(i, 0) + _sum(i, 1); }
    T sum(int l, int r) { return sum(r) - sum(l); }
};


// 51Nod. 1210
int main() {
    using LL = long long;
    int n, m, q;
    scanf("%d%d%d", &m, &n, &q);
    vector<RangeFenwick<LL>> Fw(n + 1, RangeFenwick<LL>(m + 1));
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
            int x;
            scanf("%d", &x);
            Fw[i].add(j, j + 1, x);
        }
    while (q--) {
        int x1, x2, y1, y2, z, a;
        scanf("%d%d%d%d%d%d", &y1, &x1, &y2, &x2, &z, &a);
        LL tot = 0, cnt = 0;
        for (int i = x1; i <= x2; i++) {
            tot += Fw[i].sum(y1, y2 + 1);
            cnt += y2 - y1 + 1;
        }
        if (tot < z * cnt) {
            for (int i = x1; i <= x2; i++) {
                Fw[i].add(y1, y2 + 1, a);
            }
        }
    }
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++)
            printf("%lld%c", Fw[i].sum(j, j + 1), " \n"[j == m]);
    return 0;
}
