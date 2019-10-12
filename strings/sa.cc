#include <bits/stdc++.h>
using namespace std;

template <typename T> vector<int> build_sa(const T& S, vector<int>& Sa, vector<int>& H) {
  int n = (int)S.size();
  vector<int> R(S.begin(), S.end()), U;
  Sa.resize(n + 1), iota(Sa.begin(), Sa.end(), 0), R.push_back(INT_MIN);
  for (int len = 1; len <= n; len <<= 1, R = U) {
    auto cmp = [&](int i, int j) { return R[i] != R[j] ? R[i] < R[j] : 
      (i + len <= n ? R[i + len] : INT_MIN) < (j + len <= n ? R[j + len] : INT_MIN); };
    sort(Sa.begin(), Sa.end(), cmp), U = R, U[Sa[0]] = 0;
    for (int i = 1; i <= n; i++) U[Sa[i]] = U[Sa[i - 1]] + cmp(Sa[i - 1], Sa[i]);
  }
  H.resize(n + 1), H[0] = 0;
  for (int i = 0, h = 0; i < n; H[R[i++]] = h, h -= h > 0)
    for (int j = Sa[R[i] - 1]; j + h < n && i + h < n; h++)
      if (S[j + h] != S[i + h]) break;
  return R;
}

// CF. 873F
int main() {
  using LL = long long;
  int n;
  scanf("%d", &n);
  string s, t;
  cin >> s >> t;
  reverse(s.begin(), s.end());
  reverse(t.begin(), t.end());
  vector<int> Sa, H;
  build_sa(s, Sa, H);
  vector<int> Cnt(n + 1);
  for (int i = 1; i <= n; i++) Cnt[i] = (i == 0 ? 0 : Cnt[i - 1]) + int(t[Sa[i]] == '1');
  stack<int> S;
  LL ans = 0;
  for (int i = 0; i < n; i++)
    if (t[i] == '0') {
      ans = n - i;
      break;
    }
  for (int i = 0; i <= n; i++) {
    while (!S.empty() && H[S.top()] > H[i]) {
      int t = S.top();
      S.pop();
      int r = i;
      int l = S.empty() ? 1 : S.top() + 1;
      LL len = r - l + 1 - (Cnt[r] - (l == 0 ? 0 : Cnt[l - 1]));
      if (len == 1) continue;
      LL cur = H[t] * len;
      ans = max(ans, cur);
    }
    S.push(i);
  }
  cout << ans << endl;
  return 0;
}
