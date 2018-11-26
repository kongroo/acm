#include <bits/stdc++.h>
using namespace std;


struct Hash1 {
    int n, p, m;
    vector<int> P, H;
    constexpr int mul(int x, int y, int m) { return 1LL * x * y % m; }
    constexpr int add(int x, int y, int m) { int t = x + y; return t < 0 ? t + m : t < m ? t : t - m; }
    template <typename T> Hash1(const T &S, int p = 131, int m = 1000000409) :
        n(S.size()), p(p), m(m), P(n), H(n + 1) {
        P[0] = 1, H[n] = 0;
        for (int i = 1; i < n; i++) P[i] = mul(P[i - 1], p, m);
        for (int i = n - 1; i >= 0; i--) H[i] = add(mul(H[i + 1], p, m), S[i],  m);;
    }
    int get(int l, int r) { return add(H[l], -mul(H[r], P[r - l], m), m); }
};


// CF. 126B
int main() {
    string s;
    cin >> s;
    Hash1 hs(s);
    int n = s.size();
    auto fail = []() { return puts("Just a legend"), 0; };
    if (n < 3) return fail();
    auto check = [&](int len) {
        auto t = hs.get(0, len);
        for (int i = 1; i < n - len; i++) {
            if (hs.get(i, i + len) == t) return true;
        }
        return false;
    };
    vector<int> L;
    for (int len = 1; len < n - 1; len++) {
        int l = 0, r = n - len;
        auto t = hs.get(l, l + len), u = hs.get(r, r + len);
        if (t == u) L.push_back(len);
    }
    int l = 0, r = (int)L.size();
    if (r == 0 || !check(L[0])) return fail();
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (check(L[m])) l = m;
        else r = m;
    }
    cout << s.substr(0, L[l]) << endl;
    return 0;
}
