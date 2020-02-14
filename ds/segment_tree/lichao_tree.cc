#include <bits/stdc++.h>
using namespace std;

// find maximum y coordinate of segments at x
struct LiChaoTree {
  int n;
  vector<double> segk, segb;
  vector<char> used;
  LiChaoTree(int sz) : n(1 << (32 - __builtin_clz(sz))), segk(n * 2), segb(n * 2), used(n * 2) {} 

  double intersect(double k1, double b1, double k2, double b2) { return 1.0 * (b2 - b1) / (k1 - k2); }
  void insert(double k, double b) {
    auto insert_ = [&](int o, int l, int r, double k, double b, auto fn) -> void {
      if (!used[o]) segk[o] = k, segb[o] = b, used[o] = true;
      else {
        double fl = k * l + b, fr = k * r + b;
        double gl = segk[o] * l + segb[o], gr = segk[o] * r + segb[o];
        if (fl <= gl && fr <= gr) return; else if (fl >= gl && fr >= gr) segk[o] = k, segb[o] = b; 
        else {
          int m = (l + r) >> 1;
          if (intersect(k, b, segk[o], segb[o]) < m) {
            if (fl > gl) fn(o << 1, l, m, k, b, fn);
            else {
              fn(o << 1, l, m, segk[o], segb[o], fn);
              segk[o] = k, segb[o] = b;
            }
          } else {
            if (fl > gl) {
              fn(o << 1 | 1, m, r, segk[o], segb[o], fn);
              segk[o] = k, segb[o] = b;
            } else fn(o << 1 | 1, m, r, k, b, fn);
          }
        }
      }
    };
    insert_(1, 0, n, k, b, insert_);
  }
  double query(int x) {
    auto query_ = [&](int o, int l, int r, auto fn) -> double {
      double ans = LLONG_MIN;
      if (used[o]) ans = max(ans, 1.0 * x * segk[o] + segb[o]); 
      if (l + 1 == r) return ans;
      int m = (l + r) >> 1;
      if (x < m) ans = max(ans, fn(o << 1, l, m, fn));
      else ans = max(ans, fn(o << 1 | 1, m, r, fn));
      return ans;
    };
    return query_(1, 0, n, query_);
  }
};


// CF. 1303G
using ll = long long;
int main() {
  int n;
  cin >> n;
  vector<vector<int>> g(n);
  vector<int> a(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);

  vector<char> use(n);
  vector<int> sz(n);

  auto find_c = [&](int root) {
    auto dfs = [&](int u, int p, bool b, auto f) -> int {
      if (!b) sz[u] = 1;
      for (auto v : g[u]) {
        if (v == p || use[v]) continue;
        if (!b) {
          f(v, u, b, f), sz[u] += sz[v];
        } else if (sz[v] * 2 > sz[root]) {
          return f(v, u, b, f);
        }
      }
      return u;
    };
    return dfs(root, -1, 0, dfs), dfs(root, -1, 1, dfs);
  };

  ll ans = 0;

  auto decompose = [&](int root, auto f) -> void {
    int c = find_c(root);
    se[c] = 1;
    int max_depth = sz[root] / 2;
    for (int u: g[c]) {
      if (use[u]) continue;
      f(u, f);
    }

    LiChaoTree lc(max_depth + 1);
    ans = max(ans, (ll)a[c]);
    auto dfs1 = [&](int u, int p, int dep, ll sum, ll ssum, auto f) -> void {
      sum += a[u], ssum += 1ll * (dep + 1) * a[u];
      ans = max(ans, ssum);
      lc.insert(sum, ssum); 
      for (int v: g[u]) {
        if (v == p || use[v]) continue;
        f(v, u, dep + 1, sum, ssum, f);
      }
    };
    auto dfs2 = [&](int u, int p, int dep, ll sum, ll ssum, auto f) -> void {
      sum += a[u];
      ssum += sum;
      ans = max(ans, (ll)(lc.query(dep) + 0.5) + ssum);
      for (int v: g[u]) {
        if (v == p || use[v]) continue;
        f(v, u, dep + 1, sum, ssum, f);
      }
    };
    int n_childs = g[c].size();
    lc.insert(a[c], a[c]);
    for (int i = 0; i < n_childs; ++i) {
      int u = g[c][i];
      if (use[u]) continue; 
      dfs2(u, c, 1, 0, 0, dfs2);
      dfs1(u, c, 1, a[c], a[c], dfs1);
    };
    lc = LiChaoTree(max_depth + 1);
    lc.insert(a[c], a[c]);
    for (int i = n_childs - 1; i >= 0; --i) {
      int u = g[c][i];
      if (use[u]) continue;
      dfs2(u, c, 1, 0, 0, dfs2);
      dfs1(u, c, 1, a[c], a[c], dfs1);
    }
    use[c] = 0;
  };
  decompose(0, decompose);
  cout << ans << endl;
}