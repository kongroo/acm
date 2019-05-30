#include <bits/stdc++.h>
using namespace std;

// 51Nod. 1022
int F[2002][2002], S[2002][2002];
int main() {
  int n;
  scanf("%d", &n);
  vector<int> A(n + 1);
  for (int i = 1; i <= n; i++) scanf("%d", &A[i]);
  A.insert(A.end(), A.begin() + 1, A.end());
  for (int i = 1; i <= n * 2; i++) A[i] += A[i - 1];
  memset(F, 10, sizeof F);
  for (int i = 1; i <= n * 2; i++) S[i][i] = i, F[i][i] = 0;
  for (int len = 2; len <= n * 2; len++) {
    for (int i = 1; i + len - 1 <= n * 2; i++) {
      int j = i + len - 1;
      for (int k = S[i][j - 1]; k < j && k <= S[i + 1][j]; k++) {
        int tmp = F[i][k] + F[k + 1][j];
        if (tmp < F[i][j]) F[i][j] = tmp, S[i][j] = k;
      }
      F[i][j] += A[j] - A[i - 1];
    }
  }
  auto ans = INT_MAX;
  for (int i = 1; i <= n; i++) ans = min(ans, F[i][i + n - 1]);
  printf("%d\n", ans);
  return 0;
}
