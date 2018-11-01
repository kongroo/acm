#include <bits/stdc++.h>
using namespace std;


struct Sieve {
    vector<int> L, Phi, P;
    Sieve(int n): L(n), Phi(n, 1) {
        L[1] = 1;
        for (int x = 2; x < n; x++) {
            if (!L[x]) P.push_back(L[x] = x), Phi[x] = x - 1;
            for (auto p : P) {
                if (x * p >= n) break;
                L[x * p] = p;
                Phi[x * p] = Phi[x] * (p - (x % p != 0));
                if (x % p == 0) break;
            }
        }
    }

    vector<int> factorize(long long n) {
        vector<int> R;
        for (int i = 0; 1LL * P[i] * P[i] <= n; i++) {
            if (n % P[i]) continue;
            do { n /= P[i], R.push_back(P[i]); }
            while (n % P[i] == 0);
        }
        if (n > 1) R.push_back(n);
        return R;
    }
    vector<int> factorize_low(int n) {
        assert(n < (int)L.size());
        vector<int> R;
        while (n != 1) R.push_back(L[n]), n /= L[n];
        return R;
    }
};


// 51Nod. 1188
int main() {
    using LL = long long;
    const int N = 5000000;
    auto sv = new Sieve(N + 1);
    vector<LL> Ans(N + 1);
    for (int i = 1; i <= N; i++)
        for (int j = 2; i * j <= N; j++)
            Ans[i * j] += i * sv->Phi[j];
    for (int i = 1; i <= N; i++) Ans[i] += Ans[i - 1];
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        printf("%lld\n", Ans[n]);
    }
    return 0;
}
