#include <bits/stdc++.h>
using namespace std;


template <typename T> struct RangeST {
    size_t n, h;
    vector<T> V, D;
    vector<char> B;
    function<T(T, T)> op;
    function<T(T, T, int)> alter;
    RangeST(const vector<T>& A, function<T(T, T)> op = plus<T>(),
    function<T(T, T, int)> alter = [](T v, T d, int k) { return v + d * k; }
           ): n(A.size()), h(32 - __builtin_clz(n)), V(n * 2), D(n), B(n), op(op), alter(alter) {
        copy(A.begin(), A.end(), V.begin() + n), build(0, n);
    }

    void calc(int p, int k) {
        T t = op(V[p << 1], V[p << 1 | 1]);
        V[p] = B[p] ? alter(t, D[p], k) : t;
    }
    void apply(int p, T val, int k) {
        V[p] = alter(V[p], val, k);
        if (p < (int)n) D[p] = B[p] ? alter(D[p], val, 1) : val, B[p] = true;
    }
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
                if (B[i]) apply(i << 1, D[i], k), apply(i << 1 | 1, D[i], k), B[i] = false;
    }
    void modify(int l, int r, T val) {
        assert(l < r);
        push(l, l + 1), push(r - 1, r);
        int l0 = l, r0 = r, k = 1;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1) {
            if (l & 1) apply(l++, val, k);
            if (r & 1) apply(--r, val, k);
        }
        build(l0, l0 + 1), build(r0 - 1, r0);
    }
    T query(int l, int r) {
        assert(l < r);
        push(l, l + 1), push(r - 1, r);
        T left, right;
        bool bl = false, br = false;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) left = bl ? op(left, V[l++]) : V[l++], bl = true;
            if (r & 1) right = br ? op(V[--r], right) : V[--r], br = true;
        }
        return !bl ? right : !br ? left : op(left, right);
    }
};


int main() {
    return 0;
}
