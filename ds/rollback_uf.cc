#include <bits/stdc++.h>
using namespace std;

struct RollbackUF {
  vector<int> fa;
  vector<tuple<int, int, int>> history;

  RollbackUF(int n) : fa(n, -1) {}
  int root(int x) { return fa[x] < 0 ? x : root(fa[x]); }
  int size(int x) { return -fa[root(x)]; }
  bool same(int x, int y) { return root(x) == root(y); }
  bool unite(int x, int y) {
    x = root(x), y = root(y);
    if (x != y) {
      if (fa[y] < fa[x]) swap(x, y);
      history.emplace_back(x, y, fa[y]);
      fa[x] += fa[y], fa[y] = x;
    }
    return x != y;
  }
  void rollback() {
    auto [x, y, v] = history.back();
    fa[x] -= v, fa[y] = v;
    history.pop_back();
  }
  void reset() { while (!history.empty()) rollback(); }
};


// CF. 1217F
using LL = long long;
using PII = pair<int, int>;
#define FI(i, a, b) for (int i = (a); i <= (b); ++i)
#define FD(i, a, b) for (int i = (b); i >= (a); --i)

const int N = 2e5 + 5;
int n, m, bin, last;
tuple<int, int, int> qv[N];
LL encode(int x, int y) {
  return (long long)x << 32 | y;
}

pair<int, int> decode(LL v) {
  int x = v >> 32;
  int y = int(v);
  return {x, y};
}

int main() {
  cin >> n >> m;
  bin = sqrt(m + 0.5); 
  string ans;
  for (int i = 0; i < m; ++i) {
    int t, x, y;
    scanf("%d%d%d", &t, &x, &y);
    if (x > y) swap(x, y);
    qv[i] = make_tuple(t, x, y);
  }
  unordered_set<LL> se, sse;
  vector<pair<int, int>> edges;
  RollbackUF uf(n + 1);
  for (int i = 0; i < m; ++i) {
    if (i % bin == 0) {
      for (LL v: se) {
        auto [x, y] = decode(v);
        edges.emplace_back(x, y);
      }
      se.clear();
      sse.clear();
      uf.reset();
      for (int j = i; j < m && (j == i || j % bin); ++j) {
        auto [t, x, y] = qv[j];
        if (t == 1) {
          sse.insert(encode(x, y));
          x = x % n + 1, y = y % n + 1;
          if (x > y) swap(x, y);
          sse.insert(encode(x, y));
        }
      }
      for (int i = 0; i < (int)edges.size(); ++i) {
        const auto &e = edges[i];
        LL v = encode(e.first, e.second);
        if (sse.count(v)) {
          se.insert(v);
          swap(edges[i], edges.back());
          edges.pop_back();
          --i;
        } else uf.unite(e.first, e.second);
      }
    }
    auto [t, x, y] = qv[i];
    x = (x + last - 1) % n + 1;
    y = (y + last - 1) % n + 1;
    if (x > y) swap(x, y);
    if (t == 1) {
      LL v = encode(x, y);
      if (se.count(v)) se.erase(v);
      else se.insert(v);
    } else {
      int cnt = 0;
      for (LL v: se) {
        auto [x, y] = decode(v);
        cnt += uf.unite(x, y);
      }
      last = uf.same(x, y);
      ans.push_back(last ? '1' : '0');
      while (cnt--) uf.rollback();
    }
  }
  cout << ans << endl;
}
