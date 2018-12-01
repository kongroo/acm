#include <bits/stdc++.h>
using namespace std;


template <int N = 26, int B = 'a'> struct SuffixAutomaton {
    struct State { int len = 0, link = 0; array<int, N> M; };
    int last = 1;
    vector<State> D;
    template <typename X> SuffixAutomaton(const X &Seq) : D(2) { for (auto c : Seq) insert(c); }
    void insert(int c) {
        c -= B, assert(0 <= c && c < N);
        int cur = D.size(), p = last;
        D.emplace_back(D[0]), D[cur].len = D[last].len + 1;
        while (p && !D[p].M[c]) D[p].M[c] = cur, p = D[p].link;
        if (!p) D[cur].link = 1;
        else {
            int q = D[p].M[c];
            if (D[q].len == D[p].len + 1) D[cur].link = q;
            else {
                int clone = D.size();
                D.emplace_back(D[q]), D[clone].len = D[p].len + 1;
                while (p && D[p].M[c] == q) D[p].M[c] = clone, p = D[p].link;
                D[q].link = D[cur].link = clone;
            }
        }
        last = cur;
    }
    template <typename Seq> int find(const Seq &S, int t = 1) {
        for (auto c : S) { t = D[t].M.at(c - B); if (!t) return 0; }
        return t;
    }
    template <typename Seq> Seq lcs(const Seq &S, int t = 1) {
        int len = 0, mlen = 0, pos = 0;
        for (size_t i = 0; i < S.size(); i++) {
            int c = S[i] - B;
            while (t > 1 && !D[t].M.at(c)) t = D[t].link, len = D[t].len;
            if (D[t].M.at(c)) t = D[t].M[c], len++;
            if (len > mlen) mlen = len, pos = i;
        }
        return Seq(S.begin() + pos - mlen + 1, S.begin() + pos + 1);
    }
    vector<int> get_counts() {
        vector<int> F(D.size());
        auto dp = [&](int u, auto f) -> int {
            if (F[u]) return F[u];
            for (int i = 0; i < N; i++) if (D[u].M[i]) F[u] += f(D[u].M[i], f);
            return ++F[u];
        };
        for (size_t i = 1; i < F.size(); i++) F[i] = dp(i, dp);
        return F;
    }
};


// Spoj. SUBLEX
int main() {
    ios::sync_with_stdio(0);
    string s;
    cin >> s;
    SuffixAutomaton<> sa(s);
    auto F = sa.get_counts();
    int q;
    cin >> q;
    while (q--) {
        int k, cnt = 0, u = 1;
        cin >> k;
        k++;
        string t;
        while (cnt < k) {
            int v = 0;
            cnt++;
            if (cnt == k) break;
            for (int i = 0; i < 26; i++) {
                v = sa.D[u].M[i];
                if (!v) continue;
                cnt += F[v];
                if (cnt >= k) {
                    cnt -= F[v];
                    t.push_back(i + 'a');
                    break;
                }
            }
            u = v;
            if (!u) break;
        }
        cout << t << endl;
    }
}
