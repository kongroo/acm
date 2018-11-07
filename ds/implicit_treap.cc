#include <bits/stdc++.h>
using namespace std;


namespace ITreap {
using T = int;
struct Node { T x; Node *l = 0, *r = 0; int p = rand(), c = 1; bool b = 0; Node(T x) : x(x) {} };
using P = Node*;

int cnt(P t) { return !t ? 0 : t->c; }
void update(P t) { if (!t) return ; t->c = 1 + cnt(t->l) + cnt(t->r); }
void push(P t) { if (t && t->b) {t->b = 0, swap(t->l, t->r); if (t->l) t->l->b ^= 1; if (t->r) t->r->b ^= 1;}}
P at(P t, int i) {
    return !t || (push(t), i == cnt(t->l)) ? t :
           i < cnt(t->l) ?  at(t->l, i) : at(t->r, i - cnt(t->l) - 1);
}
void split(P t, P &l, P &r, int k, int a = 0) {
    !t ? void(l = r = 0) : (push(t), k <= a + cnt(t->l)) ? (r = t, split(t->l, l, t->l, k, a)) :
    (l = t, split(t->r, t->r, r, k, a + 1 + cnt(t->l))), update(t);
}
void merge(P &t, P l, P r) {
    push(l), push(r), !l || !r ? void(t = l ? l : r) : l->p > r->p ?
    (t = l, merge(l->r, l->r, r)) : (t = r, merge(r->l, l, r->l)), update(t);
}
void insert(P &t, int i, T x) { P u, v; split(t, u, v, i); merge(u, u, new Node(x)); merge(t, u, v); }
void erase(P &t, int i) { P u = at(t, i); if (u) merge(t, u->l, u->r), delete u; }
void reverse(P t, int l, int r) {
    P u, v, w;
    split(t, u, v, l), split(v, v, w, r - l);
    v->b ^= 1, merge(t, u, v), merge(t, t, w);
}
void del(P t) { if (t) del(t->l), del(t->r), delete t; }
};


// Luogu. 3391
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    ITreap::P t = nullptr;
    for (int i = 1; i <= n; i++) ITreap::insert(t, i - 1, i);
    while (m--) {
        int l, r;
        scanf("%d%d", &l, &r);
        l--;
        ITreap::reverse(t, l, r);
    }
    for (int i = 0; i < n; i++)
        printf("%d%c", ITreap::at(t, i)->x, " \n"[i + 1 == n]);
    ITreap::del(t);
    return 0;
}
