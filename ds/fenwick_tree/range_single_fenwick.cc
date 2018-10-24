#include <bits/stdc++.h>
using namespace std;


template <typename T> struct RSFenwick {
    vector<T> V;
    RSFenwick(int n): V(n) {}
    void _add(size_t i, T x) { for (; i < V.size(); i = i + 1) V[i] += x; }
    void add(size_t l, size_t r, T x) { _add(l, x), _add(r, -x); }
    T get(int i) { T r = T(); for (; i >= 0; i = (i & (i + 1)) - 1) r += V[i]; return r; }
};


int main() {
    return 0;
}
