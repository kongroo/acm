#include <bits/stdc++.h>
using namespace std;

// Persistent Trie
template <int N = 26, int B = 'a', typename T = int>
struct PTrie {
  int n;
  vector<array<int, N>> D;
  vector<T> V;
  vector<int> Rt;
  function<T(T, T)> al;
  PTrie(function<T(T, T)> al = plus<T>()) : n(1), D(1), V(1), Rt(1, 0), al(al) {}

  template <typename Seq>
  void insert(const Seq& S, T x, T m = T()) {
    static const auto ins_ = [&](int o, size_t i, auto f) -> int {
      int no = n++, tmp;
      D.emplace_back(D[o]), V.push_back(V[o]);
      V[no] = al(V[no], i == S.size() ? x : m);
      if (i < S.size()) {
        tmp = f(D[no].at(S[i] - B), i + 1, f), D[no][S[i] - B] = tmp;
      }
      return no;
    };
    Rt.push_back(ins_(Rt.back(), 0, ins_));
  }
  template <typename Seq>
  pair<bool, T> query(const Seq& S, int t = -1) {
    int u = t < 0 ? Rt.back() : Rt.at(t);
    for (auto x : S) {
      u = D[u][x - B];
      if (!u) return {false, T()};
    }
    return {true, V[u]};
  }
};

// 51Nod. 1295
PTrie<2, '0', int> tr;
string query(int l, int r, const string& S, size_t i) {
  if (i == S.size()) return "";
  int d = 1 - S[i] + '0';
  int sum = tr.V[tr.D[r][d]] - tr.V[tr.D[l][d]];
  if (sum > 0)
    return "1" + query(tr.D[l][d], tr.D[r][d], S, i + 1);
  else
    return "0" + query(tr.D[l][1 - d], tr.D[r][1 - d], S, i + 1);
}

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  auto tostr = [](int x) { return bitset<32>(x).to_string(); };
  for (int i = 1; i <= n; i++) {
    int x;
    scanf("%d", &x);
    tr.insert(tostr(x), 1, 1);
  }
  while (q--) {
    int x, l, r;
    scanf("%d%d%d", &x, &l, &r);
    l++, r++;
    auto S = query(tr.Rt[l - 1], tr.Rt[r], tostr(x), 0);
    printf("%d\n", stoi(S, NULL, 2));
  }
  return 0;
}
