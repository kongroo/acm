#include <bits/stdc++.h>
using namespace std;
 
namespace AhoCorasick {
using T = int;
constexpr int B = 'a', N = 26;

struct Node { T val = T(), ans = -1; Node *link, *ch[N]; };

void insert(Node *o, const string &s) {
  for (auto c: s) {
    if (!o->ch[c - B]) o->ch[c - B] = new Node();
    o = o->ch[c - B];
  } 
  o->val++;
}

void build_fail(Node *root) {
  queue<Node*> qu;
  qu.push(root);
  while (!qu.empty()) {
    Node *t = qu.front();
    qu.pop();
    for (int d = 0; d < N; d++) {
      if (t->ch[d]) {
        Node *nxt = t->ch[d], *u = t->link;
        while (u && !u->ch[d]) u = u->link;
        nxt->link = u ? u->ch[d] : root, qu.push(nxt);
      }
    }
  }
}

T dp(Node *o) {
  if (o->ans != -1) return o->ans;
  if (!o->link) return o->val;
  return o->ans = o->val + dp(o->link);
}

vector<int> calc(Node *root, const string &s) {
  int n = s.size();
  vector<int> ans(n);
  Node *o = root;
  for (int i = 0; i < n; i++) {
    int c = s[i] - B;
    assert(0 <= c && c < N);
    while (o && !o->ch[c]) o = o->link;
    o = o ? o->ch[c] : root;
    ans[i] = dp(o);
  }
  return ans;
}
};
 
// CF. 1202E
int main() {
  using namespace AhoCorasick;
  using LL = long long;
  int n, m;
  string t;
  cin >> t >> n;
  vector<string> ss(n + 1);
  Node *ac = new Node();
  for (int i = 1; i <= n; i++) cin >> ss[i], insert(ac, ss[i]);
  build_fail(ac);
  m = t.length();
  auto left = calc(ac, t);
  reverse(t.begin(), t.end());
  ac = new Node();
  for (int i = 1; i <= n; i++) {
    reverse(ss[i].begin(), ss[i].end());
    insert(ac, ss[i]);
  }
  build_fail(ac);
  auto right = calc(ac, t);
  reverse(right.begin(), right.end());
  LL ans = 0;
  for (int i = 0; i + 1 < m; i++) {
    ans += 1LL * left[i] * right[i + 1];
  }
  cout << ans << endl;
}
