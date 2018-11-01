#include <bits/stdc++.h>
using namespace std;


template <typename T> struct STable {
    vector<vector<T>> F;
    function<T(T, T)> op;
    STable(const vector<T> &A,
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


// 51Nod. 1249
int main() {
    int n;
    scanf("%d", &n);
    vector<int> A(n + 1);
    for (int i = 1; i <= n; i++) scanf("%d", &A[i]);
    STable<int> st(A, [](int a, int b) { return max(a, b); });
    deque<int> D;
    auto ans = 0LL;
    for (int i = 1; i <= n; i++) {
        while (!D.empty() && A[i] < A[D.back()]) D.pop_back();
        while (!D.empty() && st.query(D.front(), i) > A[i]) D.pop_front();
        D.push_back(i), ans += D.size();
    }
    printf("%lld\n", ans);
}
