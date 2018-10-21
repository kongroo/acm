#include <bits/stdc++.h>
using namespace std;


// m must be prime
vector<int> inv_n(int n, int m = int(1e9 + 7)) {
    vector<int> Inv(n, 1);
    for (int x = 2; x < n; x++) Inv[x] = Inv[m % x] * 1LL * (m - m / x) % m;
    return Inv;
}


int main() {
    return 0;
}
