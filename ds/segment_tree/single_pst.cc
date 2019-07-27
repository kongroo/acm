#include <bits/stdc++.h>
using namespace std;

template <class T> struct SinglePST {
  using Func = function<T(T, T)>;
  Func op, al;
  struct Node { T v; int lc, rc; };
  const int n;
  const T unit;  // op(unix, x) = op(x, unit) = x
  vector<Node> D;
  vector<int> R;
  SinglePST(const vector<T>& A, Func op = plus<T>(), Func al = plus<T>(), T unit = T())
      : op(op), al(al), n(1 << (32 - __builtin_clz(A.size()))), unit(unit), D(n * 2, {unit, 0, 0}), R(1, 1) { 
    for (size_t i = 0; i < A.size(); i++) D[i + n].v = A[i];
    for (int i = n - 1; i; i--) D[i] = {op(D[i << 1].v, D[i << 1 | 1].v), i << 1, i << 1 | 1};
  }

  int get_ver(int t) { return t < 0 ? t + (int)R.size() : t; }
  void new_ver(int t = -1) { R.push_back(R[get_ver(t)]); }
  void modify(int p, T val, int t = -1) {
    const auto modify_ = [&](int o, int a, int b, auto f) -> int {
      int no = D.size(), M = (a + b) >> 1, tmp;
      D.push_back(D[o]);
      if (a == M) D[no].v = al(D[o].v, val);
      else {
        if (p < M) tmp = f(D[o].lc, a, M, f), D[no].lc = tmp;
        else tmp = f(D[o].rc, M, b, f), D[no].rc = tmp;
        D[no].v = op(D[D[no].lc].v, D[D[no].rc].v);
      }
      return no;
    };
    assert(0 <= p && p < n), R.at(get_ver(t)) = modify_(R.at(get_ver(t)), 0, n, modify_);
  }
  T query(int l, int r, int t = -1) {
    const auto query_ = [&](int o, int a, int b, auto f) -> T {
      return a >= l && b <= r ? D[o].v : b <= l || a >= r ? unit
               : op(f(D[o].lc, a, (a + b) >> 1, f), f(D[o].rc, (a + b) >> 1, b, f));
    };
    return assert(l < r && 0 <= l && r <= n), query_(R.at(get_ver(t)), 0, n, query_);
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
  for (auto x : A) pst.new_ver(), pst.modify(lower_bound(B.begin(), B.end(), x) - B.begin(), 1);
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
