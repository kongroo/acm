#include <bits/stdc++.h>
using namespace std;

template <typename T> vector<int> build_sa(const T& s, vector<int>& Sa, vector<int>& H) {
    int n = (int)s.size();
    Sa.resize(n + 1);
    H.resize(n + 1);
    iota(Sa.begin(), Sa.end(), 0);
    vector<int> Rank(s.begin(), s.end());
    Rank.push_back(INT_MIN);
    for (int len = 1; len <= n; len <<= 1) {
        auto cmp = [&](int i, int j) {
            if (Rank[i] != Rank[j]) return Rank[i] < Rank[j];
            int l = i + len >= n ? 0 : Rank[i + len];
            int r = j + len >= n ? 0 : Rank[j + len];
            return l < r;
        };
        sort(Sa.begin(), Sa.end(), cmp);
        auto Tmp(Rank);
        Tmp[Sa[0]] = 0;
        for (int i = 1; i <= n; i++) Tmp[Sa[i]] = Tmp[Sa[i - 1]] + cmp(Sa[i - 1], Sa[i]);
        Rank = Tmp;
    }
    int h = 0;
    H[0] = 0;
    for (int i = 0; i < n; i++) {
        int j = Sa[Rank[i] - 1];
        if (h > 0) h--;
        for (; j + h < n && i + h < n; h++) if (s[j + h] != s[i + h]) break;
        H[Rank[i] - 1] = h;
    }
    return Rank;
}


// CF. 873F
int main() {
    using LL = long long;
    int n;
    scanf("%d", &n);
    string s, t;
    cin >> s >> t;
    reverse(s.begin(), s.end());
    reverse(t.begin(), t.end());
    vector<int> Sa, H;
    build_sa(s, Sa, H);
    vector<int> Cnt(n + 1);
    for (int i = 1; i <= n; i++) Cnt[i] = (i == 0 ? 0 : Cnt[i - 1]) + int(t[Sa[i]] == '1');
    stack<int> S;
    LL ans = 0;
    for (int i = 0; i < n; i++) if (t[i] == '0') {
            ans = n - i;
            break;
        }
    for (int i = 0; i <= n; i++) {
        while (!S.empty() && H[S.top()] > H[i]) {
            int t = S.top();
            S.pop();
            int r = i;
            int l = S.empty() ? 1 : S.top() + 1;
            LL len = r - l + 1 - (Cnt[r] - (l == 0 ? 0 : Cnt[l - 1]));
            if (len == 1) continue;
            LL cur = H[t] * len;
            ans = max(ans, cur);
        }
        S.push(i);
    }
    cout << ans << endl;
    return 0;
}
