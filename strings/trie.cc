#include <bits/stdc++.h>
using namespace std;

template <int N = 26, int B = 'a', class T = int>
struct Trie {
  struct State {
    bool ini = true, fin = false;
    T v;
    array<int, N> M;
  };
  vector<State> D;
  function<T(T, T)> op;
  Trie(function<T(T, T)> op = plus<T>()) : D(2), op(op) {}

  template <typename Seq>
  void insert(const Seq& S, T fin, T mid = T(), int t = 1) {
    for (auto c : S) {
      c -= B, assert(0 <= c && c < N);
      if (!D[t].M[c]) D[t].M[c] = D.size(), D.emplace_back(D[0]);
      D[t].v = exchange(D[t].ini, false) ? mid : op(D[t].v, mid), t = D[t].M[c];
    }
    D[t].v = exchange(D[t].ini, false) ? fin : op(D[t].v, fin), D[t].fin = true;
  }
  template <typename Seq>
  pair<int, T> query(const Seq& S, int t = 1) {
    for (auto x : S) {
      t = D[t].M.at(x - B);
      if (!t) return {0, T()};
    }
    return {t, D[t].v};
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
    if (!p.first || !p.second)
      cout << "WRONG\n";
    else if (B.test(p.second))
      cout << "REPEAT\n";
    else
      cout << "OK\n", B.set(p.second);
  }
  return 0;
}
