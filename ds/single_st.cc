#include <bits/stdc++.h>
using namespace std;


template <typename T> struct SingleST {
    T unit; // op(x, unit) = op(unit, x) = x
    size_t n;
    vector<T> V;
    using Func = function<T(T, T)>;
    Func op, alter;
    SingleST(const vector<T>& A, T unit = T(), Func op = plus<T>(), Func alter = plus<T>()
            ): unit(unit), n(A.size()), V(n * 2, unit), op(op), alter(alter) {
        copy(A.begin(), A.end(), V.begin() + n);
        for (int i = (int)n - 1; i > 0; i--) V[i] = op(V[i << 1], V[i << 1 | 1]);
    }
    void modify(int p, T val) {
        for (p += n, V[p] = alter(V[p], val); p > 1; p >>= 1)
            V[p >> 1] = op(V[(p | 1) - 1], V[p | 1]);
    }
    T query(int l, int r) {
        assert(l < r);
        T left = unit, right = unit;
        bool bl = false, br = false;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1)
            l & 1 && (left = op(left, V[l++])), r & 1 && (right = op(V[--r], right));
        return op(left, right);
    }
};


int main() {
    return 0;
}
