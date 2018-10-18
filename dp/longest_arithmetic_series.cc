#include <bits/stdc++.h>
#define SZ(a) int((a).size())
#define FI(i,a,b) for(int i=(a);i<=(b);++i)
#define FD(i,b,a) for(int i=(b);i>=(a);--i)
using namespace std;
using LL = long long;
using PII = pair<int, int>;
LL inv(LL x, LL m) { return x > 1 ? inv(m % x, m) * (m - m / x) % m : x; }
LL powmod(LL a, LL k, LL m) { LL res = 1; for (a %= m; k; k >>= 1, a = a * a % m) if (k & 1)res = res * a % m; return res; }


// 51Nod. 1055
const int N = 10001;
short F[N][N + 1];
int main() {
    int n;
    scanf("%d", &n);
    vector<int> A(n + 1);
    FI(i, 1, n) scanf("%d", &A[i]);
    sort(A.begin() + 1, A.end());
    unordered_map<int, int> M;
    FI(i, 1, n) M[A[i]] = i;
    int ans = 2;
    for (int j = n; j >= 2; j--) {
        for (int i = j - 1; i >= 1; i--) {
            int d = A[j] - A[i];
            if (1LL * d * ans > A[n] - A[1]) break;
            int t = A[j] + d;
            if (!M.count(t)) F[i][j] = 2;
            else F[i][j] = F[j][M[t]] + 1;
            ans = max(ans, (int)F[i][j]);
        }
    }
    printf("%d\n", ans);
}
