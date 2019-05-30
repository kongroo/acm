#include <bits/stdc++.h>
using namespace std;


namespace PTreap {
using T = int;
struct Node { T x; Node *l = 0, *r = 0; int p = rand(), c = 1; Node(T x) : x(x) {} };
using P = Node *;

int cnt(P t) { return !t ? 0 : t->c; }
void up(P t) { if (t) t->c = 1 + cnt(t->l) + cnt(t->r); }
bool has(P t, T x) { return !t ? 0 : x == t->x ? 1 : has(x < t->x ? t->l : t->r, x); }
int index(P t, T x) { return !t ? 0 : x <= t->x ? index(t->l, x) : cnt(t->l) + 1 + index(t->r, x); }
int rindex(P t, T x) { return !t ? 0 : x >= t->x ? rindex(t->r, x) : cnt(t->r) + 1 + rindex(t->l, x); }
T at(P t, int i) { int u = cnt(t->l); return i == u ? t->x : i < u ? at(t->l, i) : at(t->r, i - ++u); }
void split(P t, T x, P &l, P &r) {
  P u = t ? new Node(*t) : nullptr;
  !t ? void(l = r = 0) : x < t->x ?
  (r = u, split(t->l, x, l, r->l), up(r)) : (l = u, split(t->r, x, l->r, r), up(l));
}
void merge(P &t, P l, P r) {
  !l || !r ? void(t = l ? l : r) : l->p > r->p ?
  (merge(l->r, l->r, r), up(t = l)) : (merge(r->l, l, r->l), up(t = r));
}
void insert(P &t, T x) { P u, v; split(t, x, u, v); merge(u, u, new Node(x)); merge(t, u, v); }
void erase(P &t, T x) {
  if (t) t->x == x ? merge(t, t->l, t->r) :
    (t = new Node(*t), erase(x < t->x ? t->l : t->r, x)), up(t);
}
};


// Luogu. 3369
int main() {
    using namespace PTreap;
    int n;
    scanf("%d", &n);
    vector<P> R;
    R.push_back(nullptr);
    const int INF = 2147483647;
    for (int i = 1; i <= n; i++) {
        int v, o, x;
        scanf("%d%d%d", &v, &o, &x);
        R.push_back(R[v]);
        if (o == 1) insert(R.back(), x);
        else if (o == 2) erase(R.back(), x);
        else if (o == 3) printf("%d\n", index(R.back(), x) + 1);
        else if (o == 4) printf("%d\n", at(R.back(), x - 1));
        else if (o == 5) printf("%d\n", index(R.back(), x) ? at(R.back(), index(R.back(), x) - 1) : -INF);
        else printf("%d\n", rindex(R.back(), x) ? at(R.back(), cnt(R.back()) - rindex(R.back(), x)) : INF);
    }
    return 0;
}
