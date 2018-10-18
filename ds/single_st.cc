#include <bits/stdc++.h>
using namespace std;


template <typename T> struct SingleST {
    size_t n;
    vector<T> V;
    using Func = function<T(T, T)>;
    Func op, alter;
    SingleST(const vector<T>& A, Func op = plus<T>(), Func alter = plus<T>()
            ): n(A.size()), V(n * 2), op(op), alter(alter) {
        copy(A.begin(), A.end(), V.begin() + n);
        for (int i = (int)n - 1; i > 0; i--) V[i] = op(V[i << 1], V[i << 1 | 1]);
    }
    void modify(int p, T val) {
        for (p += n, V[p] = alter(V[p], val); p > 1; p >>= 1)
            V[p >> 1] = op(V[(p | 1) - 1], V[p | 1]);
    }
    T query(int l, int r) {
        assert(l < r);
        T left = T(), right = T();
        bool bl = false, br = false;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) left = bl ? op(left, V[l++]) : V[l++], bl = true;
            if (r & 1) right = br ? op(V[--r], right) : V[--r], br = true;
        }
        return !bl ? right : !br ? left : op(left, right);
    }
};


int main() {
    return 0;
}
