#include <bits/stdc++.h>
#include <ext/rope>
using namespace std;
using namespace __gnu_cxx;

struct PDSU {
  vector<rope<int>> F;
  PDSU(int n) : F(1, rope<int>(n, -1)) {}

  int get_ver(int t) { return t < 0 ? t + (int)F.size() : t; }
  void new_ver(int t = -1) { F.emplace_back(F[get_ver(t)]); }
  void modify(int p, int x, int t = -1) {
    if (t < 0) F.emplace_back(F.back());
    F[get_ver(t)].replace(p, x);
  }
  int query(int x, int t = -1) { return F[get_ver(t)].at(x); }
  int root(int x, int t = -1) {
    int p = query(x, t);
    return p < 0 ? x : root(p, t);
  }
  bool same(int x, int y, int t = -1) { return root(x, t) == root(y, t); }
  int size(int x, int t = -1) { return -query(x, t); }
  bool unite(int x, int y, int t = -1) {
    x = root(x, t), y = root(y, t);
    if (x != y) {
      int sx = size(x, t), sy = size(y, t);
      if (sx < sy) swap(x, y);
      modify(x, -sx - sy, t), modify(y, x, t);
    }
    return x != y;
  }
};

// Luogu. 3402
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  PDSU uf(n + 1);
  for (int i = 1; i <= m; i++) {
    int t, a, b, k;
    scanf("%d", &t);
    if (t == 1) {
      scanf("%d%d", &a, &b);
      if (!uf.unite(a, b)) uf.new_ver();
    } else if (t == 2) {
      scanf("%d", &k);
      uf.new_ver(k);
    } else {
      scanf("%d%d", &a, &b);
      uf.new_ver();
      puts(uf.same(a, b) ? "1" : "0");
    }
  }
  return 0;
}
