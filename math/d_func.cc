#include <bits/stdc++.h>
using namespace std;


// Cnt of divisors, partial multiplicative function
int d_func(long long n) {
    int ret = 1;
    for (auto i = 2LL; i * i <= n; i++) {
        if (n % i == 0) {
            int cnt = 0;
            while (n % i == 0) n /= i, cnt++;
            ret *= cnt + 1;
        }
    }
    if (n > 1) ret *= 2;
    return ret;
}


// Spoj. COMDIV
int main() {
    int T;
    cin >> T;
    while (T--) {
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%d\n", dFunc(__gcd(a, b)));
    }
}
