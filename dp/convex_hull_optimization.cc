#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FI(i, a, b) for (int i = (a); i <= (b); ++i)

// CF. 1083E
const int N = 1e6 + 5;
struct State {
  int x, y;
  LL a;
};
int n, hq = 0, tq = 1, Q[N];
LL ans = 0, F[N];
State S[N];

double slope(int j, int i) { return 1. * (F[i] - F[j]) / (S[i].x - S[j].x); }
LL calc(int j, int i) { return F[j] + 1LL * S[i].y * (S[i].x - S[j].x) - S[i].a; }

int main() {
  scanf("%d", &n);
  FI(i, 1, n) scanf("%d%d%lld", &S[i].x, &S[i].y, &S[i].a);
  sort(S + 1, S + 1 + n, [&](const auto& a, const auto& b) { return a.x < b.x; });
  FI(i, 1, n) {
    while (hq + 1 < tq && calc(Q[hq], i) < calc(Q[hq + 1], i)) hq++;
    F[i] = calc(Q[hq], i);
    ans = max(ans, F[i]);
    while (hq + 1 < tq && slope(Q[tq - 2], Q[tq - 1]) < slope(Q[tq - 1], i)) tq--;
    Q[tq++] = i;
  }
  printf("%lld\n", ans);
}
