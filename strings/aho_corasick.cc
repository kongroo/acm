#include <bits/stdc++.h>
using namespace std;


template <int N = 26, int B = 'a', typename T = int> struct AhoCorasick {
    struct State { int link; T v; array<int, N> M; };
    vector<State> D;
    function<T(T, T)> op;
    bool built;
    AhoCorasick(function<T(T, T)> op = plus<T>()) : D(2), op(op), built(false) {}
    template <typename Seq> void insert(const Seq &S, T fin, T mid = T(), int t = 1) {
        for (auto c : S) {
            c -= B, assert(0 <= c && c < N);
            if (!D[t].M[c]) D[t].M[c] = D.size(), D.emplace_back(D[0]);
            D[t].v = op(D[t].v, mid), t = D[t].M[c];
        }
        D[t].v = op(D[t].v, fin), built = false;
    }
    void build_fail() {
        queue<int> Q;
        Q.push(1), built = true;
        while (!Q.empty()) {
            int t = Q.front();
            Q.pop();
            for (int c = 0; c < N; c++) if (D[t].M[c]) {
                    int nxt = D[t].M[c], u = D[t].link;
                    while (u && !D[u].M[c]) u = D[u].link;
                    D[nxt].link = u ? D[u].M[c] : 1, Q.push(nxt);
                }
        }
    }
    template <typename R, typename Seq>
    R calc(const Seq &S,  function<void(R &, T)> al, const R &init = R()) {
        if (!built) build_fail();
        R ans(init);
        int t = 1, tt;
        for (auto c : S) {
            c -= B, assert(0 <= c && c < N);
            while (t && !D[t].M[c]) t = D[t].link;
            t = t ? D[t].M[c] : 1, tt = t;
            while (tt) al(ans, D[tt].v), tt = D[tt].link;
        }
        return ans;
    }
};


// Luogu. 3796
int main() {
    ios::sync_with_stdio(0);
    int n;
    while (cin >> n && n) {
        AhoCorasick<> ac([](int x, int y) { return y; });
        vector<string> V(n + 1);
        for (int i = 1; i <= n; i++) cin >> V[i];
        for (int i = 1; i <= n; i++) ac.insert(V[i], i);
        string s;
        cin >> s;
        vector<int> Tmp(n + 1);
        auto Cnt = ac.calc<vector<int>>(s, [](vector<int> &x, int y) { x[y]++; }, vector<int>(n + 1));
        int m = *max_element(Cnt.begin() + 1, Cnt.end());
        cout << m << endl;
        for (int i = 1; i <= n; i++) if (Cnt[i] == m) cout << V[i] << endl;
    }
}
