#include <bits/stdc++.h>
using namespace std;


template <typename T> struct RangeST {
    T unit; // op(unit, x) = op(x, unit) = x, alter(x, unit, k) = x
    int n, h;
    vector<T> V, D;
    function<T(T, T)> op;
    function<T(T, T, int)> alter;
    RangeST(const vector<T>& A, T unit = T(), function<T(T, T)> op = plus<T>(),
    function<T(T, T, int)> alter = [](T v, T d, int k) { return v + d * k; }
           ): unit(unit), n(A.size()), h(32 - __builtin_clz(n)),
        V(n * 2, unit), D(n, unit), op(op), alter(alter) {
        copy(A.begin(), A.end(), V.begin() + n), build(0, n);
    }

    void calc(int p, int k) { T t = op(V[p << 1], V[p << 1 | 1]); V[p] = alter(t, D[p], k); }
    void apply(int p, T val, int k) { V[p] = alter(V[p], val, k); if (p < n) D[p] = alter(D[p], val, 1); }
    void build(int l, int r) {
        int k = 2;
        for (l += n, r += n - 1; l > 1; k <<= 1) {
            l >>= 1, r >>= 1;
            for (int i = r; i >= l; i--) calc(i, k);
        }
    }
    void push(int l, int r) {
        int s = h, k = 1 << (h - 1);
        for (l += n, r += n - 1; s > 0; --s, k >>= 1)
            for (int i = l >> s; i <= r >> s; i++)
                apply(i << 1, D[i], k), apply(i << 1 | 1, D[i], k), D[i] = unit;
    }
    void modify(int l, int r, T val) {
        assert(l < r), push(l, l + 1), push(r - 1, r);
        int l0 = l, r0 = r, k = 1;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1)
            l & 1 && apply(l++, val, k), r & 1 && apply(--r, val, k);
        build(l0, l0 + 1), build(r0 - 1, r0);
    }
    T query(int l, int r) {
        assert(l < r), push(l, l + 1), push(r - 1, r);
        T left = unit, right = unit;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1)
            l & 1 && (left = op(left, V[l++])), r & 1 && (right = op(V[--r], right));
        return op(left, right);
    }
};


int main() {
    return 0;
}
