#include <bits/stdc++.h>
using namespace std;


namespace Primality {
using LL = long long;
LL MUL(LL x, LL y, LL m) {
    LL c, s = 0;
    for (c = x % m; y; c = (c + c) % m, y >>= 1)
        if (y & 1) s = (s + c) % m;
    return s;
}
LL POW(LL x, LL y, LL m) {
    LL c, s = 1;
    for (c = x % m; y; c = MUL(c, c, m), y >>= 1)
        if (y & 1) s = MUL(s, c, m);
    return s;
}
bool miller_rabin(LL num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (~num & 1) return false;
    const int u[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022, 0};
    LL e = num - 1, a, c = 0;
    while (~e & 1) e /= 2, c++;
    for (int i = 0; u[i]; i++) {
        if (num <= u[i]) return true;
        a = POW(u[i], e, num);
        if (a == 1) continue;
        for (int j = 1; a != num - 1; j++) {
            if (j == c) return false;
            a = MUL(a, a, num);
        }
    }
    return true;
}
LL pollard_rho(LL n) {
    if (n <= 3 || miller_rabin(n)) return n;
    for (;;) {
        int i = 1, cnt = 2;
        LL x = rand() % n, y = x, c = rand() % n;
        if (!c || c == n - 2) c++;
        do {
            LL u = __gcd(n - x + y, n);
            if (u > 1 && u < n) return u;
            if (++i == cnt) y = x, cnt *= 2;
            x = (c + MUL(x, x, n)) % n;
        } while (x != y);
    }
    return n;
}
vector<LL> factorize(LL n) {
    vector<LL> u;
    for (auto x : {2, 3, 5, 7, 11, 13}) {
        while (n % x == 0) n /= x, u.push_back(x);
    }
    if (n > 1) u.push_back(n);
    for (size_t i = u.size() - 1; i < u.size(); i++) {
        LL x = pollard_rho(u[i]);
        if (x == u[i]) continue;
        u[i--] /= x;
        u.push_back(x);
    }
    sort(u.begin(), u.end());
    return u;
}
};


int main() {
    return 0;
}
