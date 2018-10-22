#include <bits/stdc++.h>
using namespace std;


template <typename T> struct RangeST {
    int n, h;
    vector<T> V, D;
    vector<char> B;
    function<T(T, T)> op;
    function<T(T, T, int)> alter;
    RangeST(const vector<T>& A, function<T(T, T)> op = plus<T>(),
    function<T(T, T, int)> alter = [](T v, T d, int k) { return v + d * k; }
           ): n(A.size()), h(32 - __builtin_clz(n)),
        V(n * 2), D(n), B(n), op(op), alter(alter) {
        copy(A.begin(), A.end(), V.begin() + n), build(0, n);
    }

    void calc(int p, int k) { T t = op(V[p << 1], V[p << 1 | 1]); V[p] = B[p] ? alter(t, D[p], k) : t; }
    void apply(int p, T val, int k) {
        V[p] = alter(V[p], val, k);
        if (p < n) D[p] = B[p] ? alter(D[p], val, 1) : val, B[p] = true;
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


int main() {
    using LL = long long;
    int n;
    scanf("%d", &n);
    vector<tuple<int, int, int, int>> A;
    const int Bias = 1e6;
    for (int i = 0; i < n; i++) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        a += Bias, b += Bias, c += Bias, d += Bias;
        A.emplace_back(a, b, c, d);
    }
    auto solve = [&]() {
        vector<tuple<int, int, int, int>> E;
        for (auto& t : A) {
            int a, b, c, d;
            tie(a, b, c, d) = t;
            E.emplace_back(a, -1, b, d);
            E.emplace_back(c, 1, b, d);
        }
        sort(E.begin(), E.end());
        using PII = pair<int, int>;
        RangeST<PII> st(vector<PII> (Bias * 2 + 1),
        [](PII a, PII b) {
            int x = min(a.first, b.first), y = a.second + b.second;
            return PII{x, y};
        },
        [](PII v, PII d, int k) {
            int x = v.first, y = v.second, z = d.first;
            x += z;
            if (z == 0) return v;
            if (x) y = k;
            else if (k == 1) y = 0;
            return PII{x, y};
        });
        LL ans = 0;
        for (auto& e : E) {
            int t, l, r;
            tie(ignore, t, l, r) = e;
            int pre = st.query(l, r + 1).second;
            st.modify(l, r + 1, {-t, 0});
            int cur = st.query(l, r + 1).second;
            ans += abs(cur - pre);
            for (int i = Bias - 15; i <= Bias + 25; i++) printf("%d", st.query(i, i + 1).second);
            printf("    %d, %d, %d   %d, %d, %lld\n", t, l, r, pre, cur, ans);
        }
        return ans;
    };
    LL ans = solve();
    for (auto& t : A) {
        int a, b, c, d;
        tie(a, b, c, d) = t;
        t = {b, a, d, c};
    }
    ans += solve();
    printf("%lld\n", ans);
    return 0;
}
