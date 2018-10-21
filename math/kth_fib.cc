#include <bits/stdc++.h>
using namespace std;

/* Fibonacci
 * F[1]+F[3]+...+F[2n-1] = F[2n]-F[2]+F[1]
 * F[2]+F[4]+...+F[2n] = F[2n+1]-F[1]
 * F[1]^2+F[2]^2+...+F[n]^2 = F[n]F[n+1]
 * F[2n] = F[n](F[n-1]+F[n+1])
 * F[2n-1] = F[n]^2 + F[n-1]^2
*/

// F[0] = 0, F[1] = 1, return {F[k], F[k-1]}
constexpr pair<int, int> kth_fib(long long k, int m = 1e9 + 7) {
    if (k <= 1) return make_pair(k, 0);
    auto t = kth_fib(k / 2, m);
    int x = t.first, y = t.second;
    int p = (1LL * x * x + 1LL * y * y) % m, q = x * (x + 2LL * y) % m;
    return k & 1 ? make_pair(int((0LL + p + q) % m), q) : make_pair(q, p);
}


int main() {
    auto p = kth_fib(1);
    printf("%d, %d\n", p.first, p.second);
    return 0;
}
