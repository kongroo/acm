#include <bits/stdc++.h>
using namespace std;


template <typename T> struct SinglePST {
    struct Node { T v; int lc, rc; };
    T unit; // op(unix, x) = op(x, unit) = x
    int n;
    vector<Node> D;
    vector<int> Rt;
    using Func = function<T(T, T)>;
    Func op, alter;
    SinglePST(const vector<T>& A, T unit = T(), Func op = plus<T>(), Func alter = plus<T>()
             ): unit(unit), n(1 << (32 - __builtin_clz(A.size()))),
        D(n * 2, {unit, 0, 0}), Rt(1, 1),  op(op), alter(alter) {
        for (size_t i = 0; i < A.size(); i++) D[i + n].v = A[i];
        for (int i = n - 1; i > 0; i--) D[i] = {op(D[i * 2].v, D[i * 2 + 1].v), i * 2, i * 2 + 1};
    }

    void modify(int p, T val) {
        static const function<int(int, int, int)> modify_ = [&](int o, int L, int R) {
            int no = D.size(), M = (L + R) / 2, tmp;
            D.push_back(D[o]);
            if (L == M)  D[no].v = alter(D[o].v, val);
            else {
                if (p < M) tmp = modify_(D[o].lc, L, M), D[no].lc = tmp;
                else tmp = modify_(D[o].rc, M, R), D[no].rc = tmp;
                D[no].v = op(D[D[no].lc].v, D[D[no].rc].v);
            }
            return no;
        };
        assert(0 <= p && p < n);
        Rt.push_back(modify_(Rt.back(), 0, n));
    }
    T query(int l, int r, int t = -1) {
        static const function<T(int, int, int)> query_ = [&](int o, int L, int R) {
            if (L >= l && R <= r) return D[o].v;
            if (R <= l || L >= r) return unit;
            int M = (L + R) / 2;
            return op(query_(D[o].lc, L, M), query_(D[o].rc, M, R));
        };
        assert(l < r && 0 <= l && r <= n && t < int(Rt.size()));
        return query_(t < 0 ? Rt.back() : Rt[t], 0, n);
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
    SinglePST<int> pst(vector<int>(B.size() + 1));
    for (auto x : A) pst.modify(lower_bound(B.begin(), B.end(), x) - B.begin(), 1);
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
