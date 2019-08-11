#include <bits/stdc++.h>
using namespace std;

struct CombineSmall {
  int m;
  vector<vector<int>> F;
  CombineSmall(int n, int m) : m(m), F(n) { for (int i = 1; i < n; i++) F[i].resize(i + 1); }
  int com(int n, int k) {
    return !k ? 1 : k > n ? 0 : k + k > n ? com(n, n - k)
      : F.at(n)[k] ? F[n][k] : F[n][k] = (com(n - 1, k) + com(n - 1, k - 1)) % m;
  }
};

int main() { return 0; }
