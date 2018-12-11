#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using PII = pair<int, int>;
#define FI(i,a,b) for(int i=(a);i<=(b);++i)
#define FD(i,b,a) for(int i=(b);i>=(a);--i)
#define DEBUG(x) cerr << #x << ": " << (x) << endl;
constexpr int inv(LL x, int m) { return x > m ? inv(x % m, m) : x > 1 ? inv(m % x, m) * (m - m / x) % m : x; }
constexpr int mpow(LL a, LL k, int m) { int r(1); for (a %= m; k; k >>= 1, a = a * a % m) if (k & 1)r = r * a % m; return r; }


// CF. 1083E
int main() {
    int n; scanf("%d", &n);
    vector<tuple<int, int, LL>> D(n + 1);
    vector<LL> F(n + 1);
    FI(i, 1, n) {
        int x, y;
        LL a;
        scanf("%d%d%lld", &x, &y, &a);
        D[i] = make_tuple(x, y, a);
    }
    sort(D.begin(), D.end());
    deque<int> Q;
    Q.push_back(0);
    LL ans = 0;
    FI(i, 1, n) {
        auto [xi, yi, ai] = D[i];
        int l = -1, r = Q.size() - 1;
        while (l + 1 < r) {
            int m = (l + r + 1) >> 1;
            int j = Q[m + 1], k = Q[m];
            if (F[j] - F[k] <= 1LL * yi * (get<0>(D[j]) - get<0>(D[k]))) r = m;
            else l = m;
        }
        F[i] = F[Q[r]] + 1LL * yi * (xi - get<0>(D[Q[r]])) - ai;
        F[i] = max(F[i], F[i - 1]);
        ans = max(ans, F[i]);
        while (Q.size() > 1) {
            int j = Q.back(), k = Q[Q.size() - 2];
            auto [xj, yj, aj] = D[j];
            auto [xk, yk, ak] = D[k];
            if (double(F[i] - F[j]) / (xi - xj) >= double(F[j] - F[k]) / (xj - xk)) Q.pop_back();
            else break;
        }
        Q.push_back(i);
    }
    cout << ans << endl;
}
