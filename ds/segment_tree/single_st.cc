#include <bits/stdc++.h>
using namespace std;


template <typename T> struct SingleST {
    int n;
    vector<T> V;
    using Func = function<T(T, T)>;
    Func op, al;
    SingleST(const vector<T>& A, Func op = plus<T>(), Func al = plus<T>()
            ): n(A.size()), V(n * 2), op(op), al(al) {
        copy(A.begin(), A.end(), V.begin() + n);
        for (int i = n - 1; i > 0; i--) V[i] = op(V[i << 1], V[i << 1 | 1]);
    }
    void modify(int p, T val) {
        for (p += n, V[p] = al(V[p], val); p > 1; p >>= 1)
            V[p >> 1] = op(V[(p | 1) - 1], V[p | 1]);
    }
    T query(int l, int r) {
        assert(l < r);
        T left, right;
        bool b1 = false, b2 = false;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) left = b1 ? op(left, V[l++]) : V[l++], b1 = true;
            if (r & 1) right = b2 ? op(V[--r], right) : V[--r], b2 = true;
        }
        return !b1 ? right : !b2 ? left : op(left, right);
    }
};


// 51Nod. 1208
int main() {
    return 0;
}
