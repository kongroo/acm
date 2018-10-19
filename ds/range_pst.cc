#include <bits/stdc++.h>
using namespace std;


template <typename T> struct RangePST {
    struct Node { T v, d; int lc, rc; };
    T unit; // op(unit, x) = op(x, unit) = x, alter(x, unit, k) = x
    int n;
    vector<Node> D;
    vector<int> Rt;
    function<T(T, T)> op;
    function<T(T, T, int)> alter;
    RangePST(const vector<T>& A, T unit = T(), function<T(T, T)> op = plus<T>(),
    function<T(T, T, int)> alter = [](T v, T d, int k) { return v + d * k; }
            ): unit(unit), n(1 << (32 - __builtin_clz(A.size()))),
        D(n * 2, {unit, unit, 0, 0}), Rt(1, 1), op(op), alter(alter) {
        for (size_t i = 0; i < A.size(); i++) D[i + n].v = A[i];
        for (int i = n - 1; i > 0; i--) D[i] = {op(D[i * 2].v, D[i * 2 + 1].v), unit, i * 2, i * 2 + 1};
    }

    void modify(int l, int r, T val) {
        static const auto modify_ = [&](int o, int L, int R, auto f) {
            if (r <= L || R <= l) return 0;
            int no = D.size(), M = (L + R) / 2;
            D.push_back(D[o]);
            if (l <= L && R <= r) {
                D[no].v = alter(D[o].v, val, R - L), D[no].d = alter(D[o].d, val, 1);
            } else {
                int lc = f(D[o].lc, L, M, f), rc = f(D[o].rc, M, R, f);
                lc&& (D[no].lc = lc), rc && (D[no].rc = rc);
                D[no].v = op(D[D[no].lc].v, D[D[no].rc].v);
            }
            return no;
        };
        assert(l < r && 0 <= l && r <= n), Rt.push_back(modify_(Rt.back(), 0, n, modify_));
    }

    T query(int l, int r, int t = -1) {
        static const auto query_ = [&](int o, int L, int R, T a, auto f) -> T {
            T na = alter(a, D[o].d, 1);
            return l <= L && R <= r ? alter(D[o].v, a, R - L) : R <= l || r <= L ? unit :
            op(f(D[o].lc, L, (L + R) / 2, na, f), f(D[o].rc, (L + R) / 2, R, na, f));
        };
        return assert(l < r && 0 <= l && r <= n), query_(t < 0 ? Rt.back() : Rt.at(t), 0, n, unit, query_);
    }

};


// 51Nod. 1175
int main() {
    int n;
    scanf("%d", &n);
    vector<int> A(n);
    for (int i = 0; i < n; i++) scanf("%d", &A[i]);
    auto B(A);
    sort(B.begin(), B.end());
    B.erase(unique(B.begin(), B.end()), B.end());
    RangePST<int> pst(vector<int>(B.size() + 1));
    for (auto x : A) {
        int t = lower_bound(B.begin(), B.end(), x) - B.begin();
        pst.modify(t, t + 1, 1);
    }
    int q;
    scanf("%d", &q);
    while (q--) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        k = r - l + 2 - k;
        int ll = -1, rr = (int)B.size() - 1;
        while (ll + 1 != rr) {
            int m = (ll + rr + 1) / 2;
            int cnt = pst.query(0, m + 1, r + 1) - pst.query(0, m + 1, l);
            if (cnt >= k) rr = m;
            else ll = m;
        }
        printf("%d\n", B[rr]);
    }
    return 0;
}
