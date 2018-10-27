#include <bits/stdc++.h>
using namespace std;


struct Combine {
    using LL = long long;
    LL m;
    vector<vector<LL>> F;
    Combine(int n, LL mod) : m(mod), F(n + 1) {
        assert(n <= 5000 && mod > 1);
        for (int i = 1; i <= n; i++) F[i].resize(i + 1), F[i][0] = 1;
    }
    LL com(int n, int k) {
        return assert(0 <= k && k <= n), k + k > n ? com(n, n - k) :
               F[n][k] ? F[n][k] : F[n][k] = (com(n - 1, k) + com(n - 1, k - 1)) % m;
    }
};

int main() {
    return 0;
}
