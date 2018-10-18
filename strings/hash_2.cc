#include <bits/stdc++.h>
using namespace std;


namespace Hash2 {
using ULL = unsigned long long;
ULL p1(131), p2(1313);
int n = 0;
vector<ULL> H[4];
template <typename T> void init(const T& S) {
    n = S.size();
    for (int i = 0; i < 4; i++) H[i].assign(n + 1, 0ULL);
    H[2][0] = H[3][0] = 1;
    for (int i = 1; i < n; i++) H[2][i] = H[2][i - 1] * p1, H[3][i] = H[3][i - 1] * p2;
    for (int i = n - 1; i >= 0; i--)
        H[0][i] = H[0][i + 1] * p1 + S[i], H[1][i] = H[1][i + 1] * p2 + S[i];
}
pair<ULL, ULL> get(int l, int r) {
    return {
        H[0][l] - H[0][r]* H[2][r - l],
        H[1][l] - H[1][r]* H[3][r - l]
    };
}
}


// CF. 126B
int main() {
    string s;
    cin >> s;
    Hash2::init(s);
    int n = s.size();
    auto fail = []() { return puts("Just a legend"), 0; };
    if (n < 3) return fail();
    auto check = [&](int len) {
        auto t = Hash2::get(0, len);
        for (int i = 1; i < n - len; i++) {
            if (Hash2::get(i, i + len) == t) return true;
        }
        return false;
    };
    vector<int> L;
    for (int len = 1; len < n - 1; len++) {
        int l = 0, r = n - len;
        auto t = Hash2::get(l, l + len), u = Hash2::get(r, r + len);
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
