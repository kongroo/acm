#include <bits/stdc++.h>
using namespace std;


// Sum of divisors, partial multiplicative function
long long s_func(long long n) {
    auto ret = 1LL;
    for (auto i = 2LL; i * i <= n; i++) {
        if (n % i == 0) {
            auto sum = 1LL, cur = 1LL;
            while (n % i == 0) n /= i, cur *= i, sum += cur;
            ret *= sum;
        }
    }
    if (n > 1) ret *= n + 1;
    return ret;
}


// Spoj. DIVSUM
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        printf("%d\n", int(sFunc(n) - n));
    }
    return 0;
}
