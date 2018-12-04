#include <bits/stdc++.h>
using namespace std;


// Luogu. 3810
int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    map<array<int, 3>, int> M;
    vector<array<int, 3>> Q;
    for (int i = 0; i < n; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        M[array<int, 3> {a, b, c}]++;
    }
    int idx = 0;
    vector<int> Dup;
    for (const auto &p : M) {
        Q.emplace_back(p.first);
        Dup.push_back(p.second);
        idx++;
    }
    vector<int> Ans(idx), I(idx), J(idx);
    vector<char> L1(idx), L2(idx);
    iota(I.begin(), I.end(), 0);
    sort(I.begin(), I.end(), [&](int i, int j) { return Q[i] < Q[j]; });
    auto dac1 = [&](int l, int r, auto f1) -> void {
        if (l + 1 >= r) return;
        int m = (l + r) >> 1;
        f1(l, m, f1), f1(m, r, f1);
        for (int i = l; i < r; i++) L1[I[i]] = i >= m;
        inplace_merge(&I[l], &I[m], &I[r], [&](int i, int j) { return Q[i][1] < Q[j][1]; });
        copy(&I[l], &I[r], &J[l]);
        auto dac2 = [&](int l, int r, auto f2) -> void {
            if (l + 1 >= r) return;
            int m = (l + r) >> 1;
            f2(l, m, f2), f2(m, r, f2);
            for (int i = l; i < r; i++) L2[J[i]] = i >= m;
            inplace_merge(&J[l], &J[m], &J[r], [&](int i, int j) { return Q[i][2] < Q[j][2]; });
            int cnt = 0;
            for (int i = l; i < r; i++) {
                int ii = J[i];
                if (!L1[ii] && !L2[ii]) cnt += Dup[ii];
                if (L1[ii] && L2[ii]) Ans[ii] += cnt;
            }
        };
        dac2(l, r, dac2);
    };
    dac1(0, idx, dac1);
    for (int i = 0; i < idx; i++) Ans[i] += Dup[i] - 1;
    vector<int> Cnt(n);
    for (int i = 0; i < idx; i++) Cnt[Ans[i]] += Dup[i];
    for (int i = 0; i < n; i++) printf("%d\n", Cnt[i]);
}
