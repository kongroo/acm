#include <bits/stdc++.h>
using namespace std;

struct UnionFind {
    vector<int> V;
    UnionFind(int n): V(n, -1) {}
    int root(int x) { return V[x] < 0 ? x : V[x] = root(V[x]); }
    int size(int x) { return -V[root(x)]; }
    bool same(int x, int y) { return root(x) == root(y); }
    bool unite(int x, int y) {
        x = root(x);
        y = root(y);
        if (x != y) {
            if (V[y] < V[x]) swap(x, y);
            V[x] += V[y];
            V[y] = x;
        }
        return x != y;
    }
};
