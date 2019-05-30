#include <bits/stdc++.h>
using namespace std;

template <class T>
long long inverse_count(const vector<T>& A) {
  auto ninv = 0LL;
  auto B(A);
  auto merge_sort = [&](int l, int r, auto f) -> void {
    if (l + 1 >= r) return;
    int m = (l + r) >> 1;
    f(l, m, f), f(m, r, f);
    for (int u = l, v = m, i = l, c = 0; i < r; i++)
      if (v == r || (u < m && A[u] < A[v]))
        ninv += c, B[i] = A[u++];
      else
        c++, B[i] = A[v++];
    copy(&B[l], &B[r], &A[l]);
  };
  merge_sort(0, A.size(), merge_sort);
  return ninv;
}

int main() {}
