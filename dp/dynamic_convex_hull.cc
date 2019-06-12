#include <bits/stdc++.h>
using namespace std;

namespace Convex {
// dp[y] = mul * f(y) + add
using LL = long long;
bool slope = false;
struct Point {
  mutable LL mul, add, k;
  bool operator<(const Point& o) const { return slope ? k < o.k : mul < o.mul; }
};
struct Container : multiset<Point> {
  const LL INF = LLONG_MAX;
  LL div(LL a, LL b) { return a / b - ((a ^ b) < 0 && a % b); }
  bool isect(multiset<Point>::iterator x, multiset<Point>::iterator y) {
    if (y == end()) return x->k = INF, false;
    x->k =
        x->mul == y->mul ? (x->add > y->add ? INF : -INF) : div(y->add - x->add, x->mul - y->mul);
    return x->k >= y->k;
  }
  void add(LL mul, LL add) {
    auto z = insert({mul, add, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->k >= y->k) isect(x, erase(y));
  }
  LL query(LL x) {
    assert(!empty());
    slope = true;
    auto l = *lower_bound({0, 0, x});
    slope = false;
    return l.mul * x + l.add;
  }
};
}  // namespace Convex

// CF. 932F
using LL = long long;
const int N = 1e5 + 5;
const double INF = 1e18;
int n;
vector<int> G[N];
LL A[N], B[N], F[N];
Convex::Container Q[N];

void dfs(int u, int p) {
  if (G[u].size() == 1u && u != 1) {
    F[u] = 0;
    Q[u].add(-B[u], 0);
    return;
  }
  LL ans = LLONG_MAX;
  vector<int> I;
  int maxi = -1, maxv = 0;
  for (int v : G[u])
    if (v != p) {
      dfs(v, u);
      ans = min(ans, Q[v].query(A[u]));
      if ((int)Q[v].size() > maxv) {
        maxi = v;
        maxv = Q[v].size();
      }
    }
  F[u] = ans;
  if (maxi != -1) {
    swap(Q[u], Q[maxi]);
    for (int v : G[u])
      if (v != p && v != maxi) {
        for (auto pp : Q[v]) Q[u].add(pp.mul, pp.add);
        Q[v].clear();
      }
  }
  Q[u].add(-B[u], -F[u]);
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) scanf("%lld", &A[i]);
  for (int i = 1; i <= n; i++) scanf("%lld", &B[i]);
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    G[u].push_back(v);
    G[v].push_back(u);
  }
  dfs(1, 0);
  for (int i = 1; i <= n; i++) printf("%lld ", F[i]);
  puts("");
  return 0;
}
