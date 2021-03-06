#include <bits/stdc++.h>
using namespace std;


namespace Treap {
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
    !t ? void(l = r = 0) : x < t->x ?
    (r = t, split(t->l, x, l, r->l), up(r)) : (l = t, split(t->r, x, l->r, r), up(l));
}
void merge(P &t, P l, P r) {
    !l || !r ? void(t = l ? l : r) : l->p > r->p ?
    (merge(l->r, l->r, r), up(t = l)) : (merge(r->l, l, r->l), up(t = r));
}
void insert(P &t, T x) { P u, v; split(t, x, u, v); merge(u, u, new Node(x)); merge(t, u, v); }
void erase(P &t, T x) { if (t) t->x == x ? merge(t, t->l, t->r) : erase(x < t->x ? t->l : t->r, x), up(t); }
};


// Luogu. 3369
int main() {
    using namespace Treap;
    int n;
    scanf("%d", &n);
    P tr = nullptr;
    while (n--) {
        int t, x;
        scanf("%d%d", &t, &x);
        if (t == 1) insert(tr, x);
        else if (t == 2) erase(tr, x);
        else if (t == 3) printf("%d\n", index(tr, x) + 1);
        else if (t == 4)  printf("%d\n", at(tr, x - 1));
        else if (t == 5) printf("%d\n", at(tr, index(tr, x) - 1));
        else printf("%d\n", at(tr, cnt(tr) - rindex(tr, x)));
    }
    return 0;
}
