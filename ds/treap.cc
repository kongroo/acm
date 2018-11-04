#include <bits/stdc++.h>
using namespace std;


namespace Treap {
using T = int;
struct Node { T x; Node *l = 0, *r = 0; int p = rand(), c = 1; Node(T x) : x(x) {} };
using P = Node*;

int cnt(P t) { return !t ? 0 : t->c; }
void update(P t) { if (!t) return ; t->c = 1 + cnt(t->l) + cnt(t->r); }
P find(P t, T x) { return !t || x == t->x ? t : find(x < t->x ? t->l : t->r, x); }
int index(P t, T x) {
    return !t ? 0 : x <= t->x ? index(t->l, x) : cnt(t->l) + 1 + index(t->r, x);
}
P at(P t, int i) {
    return !t || i == cnt(t->l) ? t : i < cnt(t->l) ? at(t->l, i) : at(t->r, i - cnt(t->l) - 1);
}
void split(P t, T x, P &l, P &r) {
    !t ? void(l = r = 0) : x < t->x ? (r = t, split(t->l, x, l, t->l)) :
    (l = t, split(t->r, x, t->r, r)), update(t);
}
void merge(P &t, P l, P r) {
    !l || !r ? void(t = l ? l : r) : l->p > r->p ?
    (t = l, merge(l->r, l->r, r)) : (t = r, merge(r->l, l, r->l)), update(t);
}
void insert(P &t, P it) {
    !t ? void(t = it) : it->p > t->p ?  (split(t, it->x, it->l, it->r), void(t = it)) :
    insert(it->x < t->x ? t->l : t->r, it), update(t);
}
void insert(P &t, T x) { insert(t, new Node(x)); }
void erase(P &t, T x) {
    !t ? void() : t->x == x ? merge(t, t->l, t->r) : erase(x < t->x ? t->l : t->r, x), update(t);
}
P prev(P t, T x) { P u; return !t ? t : t->x >= x ? prev(t->l, x) : !(u = prev(t->r, x)) ? t : u; }
P next(P t, T x) { P u; return !t ? t : t->x <= x ? next(t->r, x) : !(u = next(t->l, x)) ? t : u; }
};


// Luogu. 3369
int main() {
    int n;
    scanf("%d", &n);
    Treap::P tr = nullptr;
    while (n--) {
        int t, x;
        scanf("%d%d", &t, &x);
        if (t == 1) Treap::insert(tr, x);
        else if (t == 2) Treap::erase(tr, x);
        else if (t == 3) printf("%d\n", Treap::index(tr, x) + 1);
        else if (t == 4)  printf("%d\n", Treap::at(tr, x - 1)->x);
        else if (t == 5) printf("%d\n", Treap::prev(tr, x)->x);
        else printf("%d\n", Treap::next(tr, x)->x);
    }
    return 0;
}
