#include <bits/stdc++.h>
using namespace std;
 
template <int N = 26, int B = 'a'> struct SuffixAutomaton {
  struct Node { int len = 0, cnt = 0; Node *link = nullptr, *ch[N] = {0}; };
  Node *root, *last;
  template <typename Seq> SuffixAutomaton(const Seq& s) 
    : root(new Node()), last(root) { for (auto c : s) insert(c); }
  void insert(int c) {
    c -= B, assert(0 <= c && c < N);
    Node *cur = new Node(), *p = last;
    cur->len = last->len + 1;
    while (p && !p->ch[c]) p->ch[c] = cur, p = p->link;
    if (!p) cur->link = root;
    else {
      Node *q = p->ch[c];
      if (q->len == p->len + 1) cur->link = q;
      else {
        Node *clone = new Node(*q);
        clone->len = p->len + 1;
        while (p && p->ch[c] == q) p->ch[c] = clone, p = p->link;
        q->link = cur->link = clone;
      }
    }
    last = cur;
  }
  template <typename Seq> Node* find(const Seq& s) {
    Node *t = root;
    for (auto c : s) {
      t = t->ch[c - B];
      if (!t) return nullptr;
    }
    return t;
  }
  template <typename Seq> Seq lcs(const Seq& s) {
    Node *t = root;
    int len = 0, mlen = 0, pos = 0;
    for (size_t i = 0; i < s.size(); i++) {
      int c = s[i] - B;
      while (t != root && !t->ch[c]) t = t->link, len = t->len;
      if (t->ch[c]) t = t->ch[c], len++;
      if (len > mlen) mlen = len, pos = i;
    }
    return Seq(s.begin() + pos - mlen + 1, s.begin() + pos + 1);
  }
  int get_count(Node *o) {
    if (o->cnt) return o->cnt;
    for (int i = 0; i < N; i++) 
      if (o->ch[i]) o->cnt += get_count(o->ch[i]);
    return ++o->cnt;
  }
};
 
// Spoj. SUBLEX
int main() {
  ios::sync_with_stdio(0);
  string s;
  cin >> s;
  SuffixAutomaton<> sa(s);
  int q;
  cin >> q;
  while (q--) {
    int k, cnt = 0;
    SuffixAutomaton<>::Node *u = sa.root;
    cin >> k;
    k++;
    string t;
    while (cnt < k) {
      SuffixAutomaton<>::Node *v = nullptr; 
      cnt++;
      if (cnt == k) break;
      for (int i = 0; i < 26; i++) {
        v = u->ch[i];
        if (!v) continue;
        cnt += sa.get_count(v);
        if (cnt >= k) {
          cnt -= sa.get_count(v);
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

