#include <bits/stdc++.h>
using namespace std;

template <class T> struct RangePST {
  function<T(T, T)> op;
  function<T(T, T, int)> al;
  struct Node { T v, d; int lc, rc; };
  const int n;
  const T unit;  // op(unit, x) = op(x, unit) = x, al(x, unit, k) = x
  vector<Node> D;
  vector<int> R;
  RangePST(const vector<T>& A,  function<T(T, T)> op = plus<T>(),
           function<T(T, T, int)> al = [](T v, T d, int k) { return v + d * k; }, T unit = T())
      : op(op), al(al), n(1 << (32 - __builtin_clz(A.size()))), unit(unit), D(n * 2, {unit, unit, 0, 0}), R(1, 1) {
    for (size_t i = 0; i < A.size(); i++) D[i + n].v = A[i];
    for (int i = n - 1; i > 0; i--) D[i] = {op(D[i * 2].v, D[i * 2 + 1].v), unit, i * 2, i * 2 + 1};
  }

  int get_ver(int t) { return t < 0 ? t + (int)R.size() : t; }
  void new_ver(int t = -1) { R.push_back(R[get_ver(t)]); }
  void modify(int l, int r, T val, int t = -1) {
    const auto modify_ = [&](int o, int L, int R, auto f) {
      if (r <= L || R <= l) return 0;
      int no = D.size(), M = (L + R) / 2;
      D.push_back(D[o]);
      if (l <= L && R <= r) {
        D[no].v = al(D[o].v, val, R - L), D[no].d = al(D[o].d, val, 1);
      } else {
        int lc = f(D[o].lc, L, M, f), rc = f(D[o].rc, M, R, f);
        lc && (D[no].lc = lc), rc && (D[no].rc = rc);
        D[no].v = op(D[D[no].lc].v, D[D[no].rc].v);
      }
      return no;
    };
    assert(l < r && 0 <= l && r <= n), R[get_ver(t)] = modify_(R[get_ver(t)], 0, n, modify_);
  }

  T query(int l, int r, int t = -1) {
    const auto query_ = [&](int o, int L, int R, T a, auto f) -> T {
      T na = al(a, D[o].d, 1);
      return l <= L && R <= r ? al(D[o].v, a, R - L) : R <= l || r <= L ? unit
               : op(f(D[o].lc, L, (L + R) / 2, na, f), f(D[o].rc, (L + R) / 2, R, na, f));
    };
    return assert(l < r && 0 <= l && r <= n), query_(R[get_ver(t)], 0, n, unit, query_);
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
    pst.new_ver(), pst.modify(t, t + 1, 1);
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
      if (cnt >= k)
        rr = m;
      else
        ll = m;
    }
    printf("%d\n", B[rr]);
  }
  return 0;
}
