#include <bits/stdc++.h>
using namespace std;


template <typename T> struct STable {
    vector<vector<T>> F;
    function<T(T, T)> op;
    STable(const vector<T>& A,
    function<T(T, T)> op = [](T a, T b) { return min(a, b); }
          ): F(32 - __builtin_clz(A.size()), vector<T>(A.size())), op(op)  {
        for (size_t i = 0; i < A.size(); i++) F[0][i] = A[i];
        for (size_t c = 0; c + 1 < F.size(); c++)
            for (size_t i = 0; i < A.size(); i++)
                F[c + 1][i] = i + (1 << c) < A.size() ? op(F[c][i], F[c][i + (1 << c)]) : F[c][i];
    }
    T query(int l, int r) {
        int c = 31 - __builtin_clz(r - l);
        return assert(l < r), op(F[c][l], F[c][r - (1 << c)]);
    }
};


int main() {
    using LL = long long;
    vector<LL> A{1, -1, 2, 3, 4, 5, 3, 2, 3, 5, 10, 1};
    STable<LL> rmq(A, [](int a, int b) { return max(a, b); });
    cout << rmq.query(1, 2) << endl;
    cout << rmq.query(4, 6) << endl;
    cout << rmq.query(0, 12) << endl;
}
