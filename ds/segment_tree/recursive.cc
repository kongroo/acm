#include <bits/stdc++.h>
using namespace std;
 
template <class T> struct STree {
  int n;
  vector<int> tree, lazy;
  STree(int sz) : n(1 << (32 - __builtin_clz(sz))), tree(n * 2), lazy(n) {}
 
  void updateTree(int o, int len, int mode) {
    if (mode == 1) tree[o] = len - tree[o];
    else if (mode == 2) tree[o] = 0;
    else if (mode == 3) tree[o] = len;
  }
 
  void updateLazy(int o, int mode) {
    if (o >= n) return;
    if (mode == 1) lazy[o] ^= 1;
    else if (mode == 2) lazy[o] = 2;
    else if (mode == 3) lazy[o] = 3;
  }
 
  void push(int o, int l, int r) {
    updateLazy(o << 1, lazy[o]);
    updateLazy(o << 1 | 1, lazy[o]);
    updateTree(o << 1, (r - l) / 2, lazy[o]);
    updateTree(o << 1 | 1, (r - l) / 2, lazy[o]);
    lazy[o] = 0;
  }
 
  void modify(int l, int r, int mode) {
    auto modify_ = [&](int o, int ll, int rr, auto fn) -> void {
      if (l <= ll && rr <= r) {
        updateTree(o, rr - ll, mode);
        updateLazy(o, mode);
        return;
      }
      push(o, ll, rr);
      int mm = (ll + rr) >> 1;
      if (mm > l) fn(o << 1, ll, mm, fn);
      if (mm < r) fn(o << 1 | 1, mm, rr, fn);
      tree[o] = tree[o << 1] + tree[o << 1 | 1];
    };
    modify_(1, 0, n, modify_);
  }
 
  T query(int l, int r) {
    auto query_ = [&](int o, int ll, int rr, auto fn) -> T {
      if (l <= ll && rr <= r) return tree[o]; 
      push(o, ll, rr); 
      int mm = (ll + rr) >> 1;
      T ret = T();
      if (mm > l) ret += fn(o << 1, ll, mm, fn);
      if (mm < r) ret += fn(o << 1 | 1, mm, rr, fn);
      return ret;
    };
    return query_(1, 0, n, query_);
  }
 
  int first_zero() {
    auto dfs = [&](int o, int ll, int rr, auto fn) -> int {
      if (tree[o] == rr - ll) return -1;
      if (ll + 1 == rr) return o;
      push(o, ll, rr);
      int mm = (ll + rr) >> 1;
      int left = fn(o << 1, ll, mm, fn);
      if (left != -1) return left;
      return fn(o << 1 | 1, mm, rr, fn);
    };
    return dfs(1, 0, n, dfs) - n;
  }
};
 
// CF. 817F
using LL = long long;
const int N = 1e5 + 5;
 
int main() {
  int n;
  cin >> n;
  vector<tuple<int, LL, LL>> qs(n + 1);
  vector<LL> vals;
  for (int i = 1; i <= n; i++) {
    int t;
    LL l, r;
    scanf("%d%lld%lld", &t, &l, &r);
    qs[i] = make_tuple(t, l, r);
    vals.push_back(l);
    vals.push_back(r + 1);
  }
  vals.push_back(1);
  sort(vals.begin(), vals.end());
  vals.erase(unique(vals.begin(), vals.end()), vals.end());
  STree<int> st(vals.size());
  for (int i = 1; i <= n; i++) {
    auto [t, l, r] = qs[i];
    int il = lower_bound(vals.begin(), vals.end(), l) - vals.begin();
    int ir = lower_bound(vals.begin(), vals.end(), r + 1) - vals.begin();
    st.modify(il, ir, t == 1 ? 3 : t == 2 ? 2 : 1);
    int idx = st.first_zero();
    printf("%lld\n", vals[idx]);
  }
  return 0;
}
