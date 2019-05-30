#include <bits/stdc++.h>
using namespace std;

// Z[0] = 0, Z[i] is max that let s[0..Z[i]-1] == s[i..i+Z[i]-1]
template <typename T>
vector<int> get_z(const T& s) {
  int n = int(s.size());
  vector<int> Z(n);
  for (int i = 1, l = 0, r = 0; i < n; i++) {
    if (i <= r) Z[i] = min(r - i, Z[i - l]);
    while (i + Z[i] < n && s[i + Z[i]] == s[Z[i]]) Z[i]++;
    if (r <= i + Z[i]) l = i, r = i + Z[i];
  }
  return Z;
}

// CF. 1051E
int main() {
  using LL = long long;
  const int Mod = 998244353;
  const int N = 1e6 + 5;
  vector<LL> F(N), S(N);
  string a, l, r;
  cin >> a >> l >> r;
  int n = a.size();
  F[n] = S[n] = 1;
  auto Z1 = get_z(l + "#" + a);
  auto Z2 = get_z(r + "#" + a);
  int lenL = int(l.length()), lenR = int(r.length());
  for (int i = n - 1; i >= 0; i--) {
    if (a[i] == '0') {
      if (l == "0")
        F[i] = F[i + 1];
      else
        F[i] = 0;
    } else {
      if (lenR == 1 && r < a.substr(i, 1)) return !printf("0\n");
      int x = i + lenL - 1, y = i + lenR - 1;
      x = min(x, n), y = min(y, n);
      if (x < n) {
        int pos = Z1[lenL + 1 + i];
        if (pos < lenL && a[i + pos] < l[pos]) x++;
      }
      if (y < n) {
        int pos = Z2[lenR + 1 + i];
        if (pos < lenR && r[pos] < a[i + pos]) y--;
      }
      F[i] = (S[x + 1] - S[y + 2] + Mod) % Mod;
    }
    S[i] = (S[i + 1] + F[i]) % Mod;
  }
  cout << F[0] << endl;
  return 0;
}
