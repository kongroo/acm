#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using PII = pair<int, int>;

// CF. 835F
const int N = 2e5 + 5;
int n, rt, Use[N], Dis[N], In[N], tp = 0, Path[N];
vector<PII> G[N];
LL Pre[N], Suf[N], Fir[N], Las[N], F[N], H[N];

int findcycle(int u, int p) {
  if (Use[u]) return rt = u, 1;
  Use[u] = 1;
  for (auto [v, w] : G[u])
    if (v != p) {
      int ret = findcycle(v, u);
      if (ret == 1) {
        Dis[++tp] = w, Path[tp] = u, In[u] = 1;
        if (u != rt) return 1;
      }
      if (ret) return 2;
    }
  return 0;
}
void dp(int u, int p) {
  LL m1 = 0, m2 = 0, tmp;
  for (auto [v, w] : G[u])
    if (v != p && !In[v]) {
      dp(v, u), tmp = F[v] + w;
      if (tmp > m1)
        m2 = m1, m1 = tmp;
      else if (tmp > m2)
        m2 = tmp;
      H[u] = max(H[v], H[u]);
    }
  F[u] = m1, H[u] = max(H[u], m1 + m2);
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    int u, v, l;
    scanf("%d%d%d", &u, &v, &l);
    G[u].emplace_back(v, l);
    G[v].emplace_back(u, l);
  }
  findcycle(1, -1);
  LL mx = 0, len = 0;
  for (int i = 1, u; i <= tp; i++) {
    u = Path[i], dp(u, -1);
    Fir[i] = max(Fir[i - 1], len + F[u]);
    Pre[i] = max(Pre[i - 1], max(H[u], F[u] + mx));
    if (F[u] > mx) mx = F[u];
    mx += Dis[i + 1], len += Dis[i + 1];
  }
  mx = 0, len = 0;
  for (int i = tp, u; i >= 1; i--) {
    u = Path[i];
    Las[i] = max(Las[i + 1], len + F[u]);
    Suf[i] = max(Suf[i + 1], max(H[u], F[u] + mx));
    if (F[u] > mx) mx = F[u];
    mx += Dis[i], len += Dis[i];
  }
  LL ans = Pre[tp];
  for (int i = 1; i < tp; i++) {
    ans = min(ans, max({Pre[i], Suf[i + 1], Dis[1] + Fir[i] + Las[i + 1]}));
  }
  printf("%lld\n", ans);
  return 0;
}
