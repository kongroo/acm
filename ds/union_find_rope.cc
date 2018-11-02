#include <bits/stdc++.h>
#include <ext/rope>
using namespace std;
using namespace __gnu_cxx;


struct PUnionFind {
    vector<rope<int>> F;
    PUnionFind(int n): F(1, rope<int>(n, -1)) {}
    int root(int x, int t = -1) {
        if (t < 0) t = (int)F.size() - 1;
        int p = F.at(t).at(x), a;
        if (p < 0 || p == x) return x;
        else { a = root(p, t); if (a != p) F[t].replace(x, a); return a; }
    }
    int size(int x, int t = -1) { return -(t < 0 ? F.back() : F.at(t)).at(x); }
    bool same(int x, int y, int t = -1) { return root(x, t) == root(y, t); }
    bool unite(int x, int y, int t = -1) {
        if (t < 0) t = F.size(), F.emplace_back(F.back());
        x = root(x), y = root(y);
        if (x != y) {
            int sx = size(x), sy = size(y);
            if (sy > sx) swap(x, y);
            F.at(t).replace(x, -sx - sy);
            F.at(t).replace(y, x);
        }
        return x != y;
    }
};


int main() {
    PUnionFind uf(100);
    uf.unite(1, 2);
    uf.unite(2, 3);
    uf.unite(2, 5);
    uf.unite(1, 4, 0);
    uf.unite(1, 4, 2);
    cout << uf.same(1, 4) << endl;
    cout << uf.same(1, 4, 0) << endl;
    cout << uf.same(1, 4, 1) << endl;
    cout << uf.same(1, 4, 2) << endl;
    cout << uf.same(1, 4, 3) << endl;
    return 0;
}
