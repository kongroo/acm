#include <bits/stdc++.h>
using namespace std;


namespace Hash1 {
using ULL = unsigned long long;
ULL seed(131);
int n = 0;
vector<ULL> P, H;
template <typename T> void init(const T& S) {
    n = S.size();
    P.resize(n);
    H.resize(n + 1);
    P[0] = 1, H[n] = 0;
    for (int i = 1; i < n; i++) P[i] = P[i - 1] * seed;
    for (int i = n - 1; i >= 0; i--) H[i] = H[i + 1] * seed + S[i];
}
ULL get(int l, int r) { return H[l] - H[r] * P[r - l]; }
}


// CF. 126B
int main() {
    string s;
    cin >> s;
    Hash1::init(s);
    int n = s.size();
    auto fail = []() { return puts("Just a legend"), 0; };
    if (n < 3) return fail();
    auto check = [&](int len) {
        auto t = Hash1::get(0, len);
        for (int i = 1; i < n - len; i++) {
            if (Hash1::get(i, i + len) == t) return true;
        }
        return false;
    };
    vector<int> L;
    for (int len = 1; len < n - 1; len++) {
        int l = 0, r = n - len;
        auto t = Hash1::get(l, l + len), u = Hash1::get(r, r + len);
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
