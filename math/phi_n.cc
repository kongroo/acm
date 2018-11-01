#include <bits/stdc++.h>
using namespace std;


vector<int> phi_n(int n) {
    vector<int> L(n), P, Phi(n);
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
    return Phi;
}


// 51Nod. 1188
int main() {
    using LL = long long;
    const int N = 5000000;
    auto Phi = phi_n(N + 1);
    vector<LL> Ans(N + 1);
    for (int i = 1; i <= N; i++)
        for (int j = 2; i * j <= N; j++)
            Ans[i * j] += i * Phi[j];
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
