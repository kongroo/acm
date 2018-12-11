#include <bits/stdc++.h>
using namespace std;


template <class It, class Cmp>
void bubble_sort(It l, It r, Cmp cmp) {
    for (It u = r; u > l; --u)
        for (It i = l; i < u; ++i)
            if (cmp(*(i + 1), *i)) swap(*i, *(i + 1));
}
template <class It> void bubble_sort(It l, It r) {
    bubble_sort(l, r, less<decltype(*l)>());
}


template <class It, class Cmp>
void selection_sort(It l, It r, Cmp cmp) {
    for (It u = l; u < r; ++u)
        for (It i = u + 1; i < r; ++i)
            if (cmp(*i, *u)) swap(*i, *u);
}
template <class It> void selection_sort(It l, It r) {
    selection_sort(l, r, less<decltype(*l)>());
}


template <class It, class Cmp>
void insertion_sort(It l, It r, Cmp cmp) {
    for (It u = l; u < r; ++u)
        for (It i = u; i > l && cmp(*i, *(i - 1)); --i)
            swap(*i, *(i - 1));
}
template <class It> void insertion_sort(It l, It r) {
    insertion_sort(l, r, less<decltype(*l)>());
}


template <class It, class Cmp>
void merge_sort(It l, It r, Cmp cmp) {
    if (distance(l, r) < 2) return;
    It m = l + distance(l, r) / 2;
    merge_sort(l, m, cmp), merge_sort(m, r, cmp);
    inplace_merge(l, m, r, cmp);
}
template <class It> void merge_sort(It l, It r) {
    merge_sort(l, r, less<decltype(*l)>());
}


template <class It, class Cmp>
void quick_sort(It l, It r, Cmp cmp) {
    if (distance(l, r) < 2) return;
    if (distance(l, r) <= 20) return insertion_sort(l, r, cmp);
    const auto &a = *l, &b = *(r - 1), &c = *(l + distance(l, r) / 2);
    auto pivot = max(min(a, b, cmp), min(max(a, b, cmp), c, cmp), cmp);
    It u = l, v  = r;
    for (It i = u; i < v; ++i, i = max(i, u))
        if (cmp(*i, pivot)) swap(*i--, *u++);
        else if (cmp(pivot, *i)) swap(*i--, *--v);
    quick_sort(l, u, cmp), quick_sort(v, r, cmp);
}
template <class It> void quick_sort(It l, It r) {
    quick_sort(l, r, less<decltype(*l)>());
}


int main() {
    int n;
    scanf("%d", &n);
    vector<int> A(n);
    for (int i = 0; i < n; i++) scanf("%d", &A[i]);
    quick_sort(A.begin(), A.end());
    for (int i = 0; i < n; i++) printf("%d%c", A[i], " \n"[i + 1 == n]);
}
