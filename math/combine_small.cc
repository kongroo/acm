#include <bits/stdc++.h>
using namespace std;


struct CombineSmall {
    using LL = long long;
    LL m;
    vector<vector<LL>> F;
    CombineSmall(int n, LL m) : m(m), F(n) {
        assert(n <= 5001 && m > 1);
        for (int i = 1; i < n; i++) F[i].resize(i + 1), F[i][0] = 1;
    }
    LL com(int n, int k) {
        return assert(0 <= k && k <= n), k + k > n ? com(n, n - k) :
               F.at(n)[k] ? F[n][k] : F[n][k] = (com(n - 1, k) + com(n - 1, k - 1)) % m;
    }
};


int main() {
    return 0;
}
