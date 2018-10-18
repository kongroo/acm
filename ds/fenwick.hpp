#include <bits/stdc++.h>
using namespace std;

template <typename T> struct Fenwick {
    vector<T> V;
    Fenwick(int n): V(n) {}
    void add(size_t i, T x) { for (; i < V.size(); i |= i + 1) V[i] += x; }
    T sum(int i) {
        T r = T();
        for (--i; i >= 0; i = (i & (i + 1)) - 1) r += V[i];
        return r;
    }
    T sum(int l, int r) { return sum(r) - sum(l); }
};


template <class T> struct RangeSingleFenwick {
    vector<T> V;
    RangeSingleFenwick(int n): V(n, T()) {}
    void add(size_t l, size_t r, T x) {
        for (size_t i = l; i < V.size(); i |= i + 1) V[i] += x;
        for (size_t i = r; i < V.size(); i |= i + 1) V[i] += -x;
    }
    T get(int i) {
        T r = T();
        for (; i >= 0; i = (i & (i + 1)) - 1) r += V[i];
        return r;
    }
};
