#include <bits/stdc++.h>
using namespace std;


template <class T> struct RangeST {
    const int n, h;
    vector<T> V, D;
    vector<char> B;
    function<T(T, T)> op;
    function<T(T, T, int)> al;
    RangeST(const vector<T>& A, function<T(T, T)> op = plus<T>(),
    function<T(T, T, int)> al = [](T v, T d, int k) { return v + d * k; }
           ): n(A.size()), h(32 - __builtin_clz(n)),
        V(n * 2), D(n), B(n), op(op), al(al) {
        copy(A.begin(), A.end(), V.begin() + n), build(0, n);
    }

    void calc(int p, int k) { T t = op(V[p << 1], V[p << 1 | 1]); V[p] = B[p] ? al(t, D[p], k) : t; }
    void apply(int p, T val, int k) {
        V[p] = al(V[p], val, k);
        if (p < n) D[p] = B[p] ? al(D[p], val, 1) : val, B[p] = true;
    }
    void build(int l, int r) {
        l += n, r += n - 1;
        for (int k = 2; l > 1; k <<= 1) {
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
        assert(l < r), push(l, l + 1), push(r - 1, r);
        int l0 = l, r0 = r, k = 1;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1) {
            if (l & 1) apply(l++, val, k);
            if (r & 1) apply(--r, val, k);
        }
        build(l0, l0 + 1), build(r0 - 1, r0);
    }
    T query(int l, int r) {
        assert(l < r), push(l, l + 1), push(r - 1, r);
        T left, right;
        bool b1 = false, b2 = false;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) left = b1 ? op(left, V[l++]) : V[l++], b1 = true;
            if (r & 1) right = b2 ? op(V[--r], right) : V[--r], b2 = true;
        }
        return !b1 ? right : !b2 ? left : op(left, right);
    }
};


// 51Nod. 1208
int main() {
    int n, w, h;
    scanf("%d%d%d", &n, &w, &h);
    vector<array<int, 4>> E;
    vector<int> Y;
    for (int i = 0; i < n; i++) {
        int x, y, l;
        scanf("%d%d%d", &x, &y, &l);
        E.push_back({x, -1, y, l});
        E.push_back({x + w, 1, y, -l});
        Y.push_back(y), Y.push_back(y + h);
    }
    sort(Y.begin(), Y.end());
    Y.erase(unique(Y.begin(), Y.end()), Y.end());
    sort(E.begin(), E.end());
    int ans = 0;
    RangeST<int> st(vector<int>(Y.size() + 1),
    [](int x, int y) { return max(x, y); },
    [](int v, int d, int k) { return v + d; });
    for (auto& e : E) {
        int y = e[2], l = e[3];
        int i = lower_bound(Y.begin(), Y.end(), y) - Y.begin();
        int j = upper_bound(Y.begin(), Y.end(), y + h) - Y.begin();
        st.modify(i, j, l);
        ans = max(ans, st.query(0, Y.size()));
    }
    printf("%d\n", ans);
    return 0;
}
