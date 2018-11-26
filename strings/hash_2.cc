#include <bits/stdc++.h>
using namespace std;


struct Hash2 {
    int n, p1, p2, m1, m2;
    vector<int> H[4];
    constexpr int mul(int x, int y, int m) { return 1LL * x * y % m; }
    constexpr int add(int x, int y, int m) { int t = x + y; return t < 0 ? t + m : t < m ? t : t - m; }
    template <typename T> Hash2(const T &S, int p1 = 131, int p2 = 1313, int m1 = 1e9 + 7,
                                int m2 = 1e9 + 9): n(S.size()), p1(p1), p2(p2), m1(m1), m2(m2) {
        for (int i = 0; i < 4; i++) H[i].assign(n + 1, 0ULL);
        H[2][0] = H[3][0] = 1;
        for (int i = 1; i < n; i++) H[2][i] = mul(H[2][i - 1], p1, m1), H[3][i] = mul(H[3][i - 1], p2, m2);
        for (int i = n - 1; i >= 0; i--) {
            H[0][i] = add(mul(H[0][i + 1], p1, m1), S[i], m1);
            H[1][i] = add(mul(H[1][i + 1], p2, m2), S[i], m2);
        }
    }
    pair<int, int> get(int l, int r) {
        return {
            add(H[0][l], -mul(H[0][r], H[2][r - l], m1), m1),
            add(H[1][l], -mul(H[1][r], H[3][r - l], m2), m2)
        };
    }
};


// CF. 126B
int main() {
    string s;
    cin >> s;
    Hash2 hs(s);
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
