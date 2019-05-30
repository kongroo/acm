#include <bits/stdc++.h>
using namespace std;

// P[0] = 0, P[i] is the length of longest proper prefix
// of S[0...i] that is also a suffix of it
template <typename T>
vector<int> get_p(const T& S) {
  vector<int> P(S.size());
  for (int l = 0, r = 1; r < (int)S.size(); r++) {
    while (l && S[l] != S[r]) l = P[l - 1];
    if (S[l] == S[r]) P[r] = ++l;
  }
  return P;
}

// 51Nod. 1277
int main() {
  string s;
  cin >> s;
  int n = s.size();
  auto P = get_p(s);
  vector<int> F(n);
  for (int i = n - 1; i >= 0; i--) {
    F[i]++;
    int t = P[i] - 1;
    if (t < 0) continue;
    F[t] += F[i];
  }
  auto ans = 0LL;
  for (int i = 0; i < n; i++) ans = max(ans, 1LL * F[i] * (i + 1));
  cout << ans << endl;
  return 0;
}
