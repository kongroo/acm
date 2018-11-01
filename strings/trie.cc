#include <bits/stdc++.h>
using namespace std;


template <int N = 26, int B = 'a', typename T = int> struct Trie {
    int n;
    vector<array<int, N>> D;
    vector<T> V;
    function<T(T, T)> al;
    Trie(function<T(T, T)> al = plus<T>()): n(1), D(1), V(1), al(al) {}

    template <typename Seq> void insert(const Seq &S, T x, T m = T(), int u = 0) {
        for (auto c : S) {
            if (!D[u][c - B]) D[u][c - B] = n++, D.resize(n), V.resize(n);
            V[u] = al(V[u], m), u = D[u][c - B];
        }
        V[u] = al(V[u], x);
    }
    template <typename Seq> pair<bool, T> query(const Seq &S, int u = 0) {
        for (auto x : S) { u = D[u][x - B]; if (!u) return {false, T()}; }
        return {true, V[u]};
    }
};


// Luogu.2580
int main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    Trie<> tr;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        tr.insert(s, i);
    }
    int q;
    cin >> q;
    bitset<10005> B;
    while (q--) {
        string s;
        cin >> s;
        auto p = tr.query(s);
        if (!p.first || !p.second) cout << "WRONG\n";
        else if (B.test(p.second)) cout << "REPEAT\n";
        else cout << "OK\n", B.set(p.second);
    }
    return 0;
}
