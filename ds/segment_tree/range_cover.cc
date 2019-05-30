#include <bits/stdc++.h>
using namespace std;

struct RangeCover {
  int n;
  vector<int> C, S;
  RangeCover(int n) : n(n), C(n * 2), S(n * 2) {}

  void apply(int p, int v, int k) {
    C[p] += v, assert(C[p] >= 0), S[p] = C[p] ? k : p < n ? S[p << 1] + S[p << 1 | 1] : 0;
  }
  void build(int p) {
    for (int k = 2; p > 1; k <<= 1) p >>= 1, apply(p, 0, k);
  }
  void modify(int l, int r, int v) {
    assert(l < r);
    int l0 = l, r0 = r, k = 1;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1) {
      if (l & 1) apply(l++, v, k);
      if (r & 1) apply(--r, v, k);
    }
    build(l0 + n), build(r0 - 1 + n);
  }
  int ans() const { return S[1]; }
};

// 51Nod. 1206
int main() {
  using LL = long long;
  int n;
  scanf("%d", &n);
  vector<array<int, 4>> A;
  const int Bias = 1e6;
  for (int i = 0; i < n; i++) {
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    a += Bias, b += Bias, c += Bias, d += Bias;
    A.push_back({a, b, c, d});
  }
  auto solve = [&]() {
    vector<array<int, 4>> E;
    for (auto& t : A) {
      E.push_back({t[0], -1, t[1], t[3]});
      E.push_back({t[2], 1, t[1], t[3]});
    }
    sort(E.begin(), E.end());
    RangeCover rc(Bias * 2 + 1);
    LL ans = 0;
    for (auto& e : E) {
      int pre = rc.ans();
      rc.modify(e[2], e[3], -e[1]);
      int cur = rc.ans();
      ans += abs(cur - pre);
    }
    return ans;
  };
  LL ans = solve();
  for (auto& t : A) t = {t[1], t[0], t[3], t[2]};
  ans += solve();
  printf("%lld\n", ans);
  return 0;
}
