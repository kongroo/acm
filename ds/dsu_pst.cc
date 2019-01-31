#include <bits/stdc++.h>
using namespace std;


struct PDSU {
    const int n;
    vector<array<int, 2>> D;
    vector<int> V, R;
    PDSU(int n): n(n), D(n), V(n, -1), R(1, 1) {
        for (int i = n - 1; i; i--) D[i] = {i << 1, i << 1 | 1};
        for (auto &d : D) for (int i : {0, 1}) if (d[i] >= n) d[i] -= n;
    }

    int get_ver(int t) { return t < 0 ? t + (int)R.size() : t; }
    void new_ver(int t = -1) { R.push_back(R[get_ver(t)]); }
    void modify(int p, int x, int t = -1) {
        int h = 30 - __builtin_clz(p += n), no = D.size(), tmp = no, o, i;
        assert(n <= p && p < n + n), D.resize((int)D.size() + h + 1);
        for (o = R[get_ver(t)]; h; ++no, --h)
            i = !!(1 << h & p), D[no] = D[o], D[no][i] = no + 1, o = D[o][i];
        D[no] = D[o], D[no][p & 1] = V.size(), V.push_back(x), R[get_ver(t)] = tmp;
    }
    int query(int p, int t = -1) {
        int o = R[get_ver(t)];
        for (int h = 30 - __builtin_clz(p += n); h >= 0; h--) o = D[o][!!(1 << h & p)];
        return V[o];
    }
    int root(int x, int t = -1) { int p = query(x, t); return p < 0 ? x : root(p, t); }
    bool same(int x, int y, int t = -1) { return root(x, t) == root(y, t); }
    int size(int x, int t = -1) { return -query(root(x, t), t); }
    bool unite(int x, int y, int t = -1) {
        x = root(x, t), y = root(y, t);
        if (x != y) {
            int sx = size(x, t), sy = size(y, t);
            if (sx < sy) swap(x, y);
            modify(x, -sx - sy, t), modify(y, x, t);
        }
        return x != y;
    }
};


// Luogu. 3402
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    PDSU uf(n + 1);
    for (int i = 1; i <= m; i++) {
        int t, a, b, k;
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d%d", &a, &b);
            uf.new_ver();
            uf.unite(a, b);
        } else if (t == 2) {
            scanf("%d", &k);
            uf.new_ver(k);
        } else {
            scanf("%d%d", &a, &b);
            uf.new_ver();
            puts(uf.same(a, b) ? "1" : "0");
        }
    }
    return 0;
}
