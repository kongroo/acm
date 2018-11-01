#include <bits/stdc++.h>
using namespace std;

struct UnionFind {
    vector<int> F;
    UnionFind(int n): F(n, -1) {}
    int root(int x) { return F[x] < 0 ? x : F[x] = root(F[x]); }
    int size(int x) { return -F[root(x)]; }
    bool same(int x, int y) { return root(x) == root(y); }
    bool unite(int x, int y) {
        x = root(x), y = root(y);
        if (x != y) { if (F[y] < F[x]) swap(x, y); F[x] += F[y], F[y] = x; }
        return x != y;
    }
};
