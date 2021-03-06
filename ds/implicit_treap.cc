#include <bits/stdc++.h>
using namespace std;


namespace ITreap {
using T = int;
struct Node { T x; Node *l = 0, *r = 0; int p = rand(), c = 1; bool b = 0; Node(T x) : x(x) {} };
using P = Node *;

int cnt(P t) { return !t ? 0 : t->c; }
void up(P t) { if (t) t->c = 1 + cnt(t->l) + cnt(t->r); }
void push(P t) { if (t && t->b) {t->b = 0, swap(t->l, t->r); if (t->l) t->l->b ^= 1; if (t->r) t->r->b ^= 1;}}
T at(P t, int i) { push(t); int u = cnt(t->l); return i == u ? t->x : i < u ? at(t->l, i) : at(t->r, i - ++u); }
void split(P t, P &l, P &r, int k, int a = 0) {
    !t ? void(l = r = 0) : (push(t), k <= a + cnt(t->l)) ?
    (r = t, split(t->l, l, r->l, k, a), up(r)) :
    (l = t, split(t->r, l->r, r, k, a + 1 + cnt(t->l)), up(l));
}
void merge(P &t, P l, P r) {
    push(l), push(r), !l || !r ? void(t = l ? l : r) : l->p > r->p ?
    (merge(l->r, l->r, r), up(t = l)) : (merge(r->l, l, r->l), up(t = r));
}
void insert(P &t, int i, T x) { P u, v; split(t, u, v, i); merge(u, u, new Node(x)); merge(t, u, v); }
void erase(P &t, int i) {
    if (t) cnt(t->l) == i ? merge(t, t->l, t->r) :
        cnt(t->l) > i ? erase(t->l, i) : erase(t->r, i - cnt(t->l) - 1), up(t);
}
void reverse(P &t, int l, int r) {
    P u, v, w;
    split(t, u, v, l), split(v, v, w, r - l);
    v->b ^= 1, merge(t, u, v), merge(t, t, w);
}
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
        printf("%d%c", ITreap::at(t, i), " \n"[i + 1 == n]);
    return 0;
}
