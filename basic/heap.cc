#include <bits/stdc++.h>

#include <utility>
using namespace std;

template <typename T> struct Heap {
  vector<T> D;
  function<bool(T, T)> cmp;
  explicit Heap(function<bool(T, T)> cmp = less<T>()) : D(1), cmp(move(cmp)) {}

  void push(const T& x) {
    D.emplace_back(x);
    for (int t = D.size() - 1; t > 1; t >>= 1)
      if (cmp(D[t], D[t >> 1])) swap(D[t], D[t >> 1]);
  }
  T top() const { return D[1]; }
  void pop() {
    swap(D.at(1), D.back()), D.pop_back();
    for (size_t t = 1;;) {
      bool b1 = (t << 1) < D.size() && cmp(D[t << 1], D[t]);
      bool b2 =
          (t << 1 | 1) < D.size() && cmp(D[t << 1 | 1], D[t]) && cmp(D[t << 1 | 1], D[t << 1]);
      if (!b1 && !b2)
        break;
      else if (b2)
        swap(D[t], D[t << 1 | 1]), t = t << 1 | 1;
      else
        swap(D[t], D[t << 1]), t <<= 1;
    }
  }
};

// Luogu. 3378
int main() {
  int n;
  scanf("%d", &n);
  Heap<int> hp;
  for (int i = 0; i < n; i++) {
    int t;
    scanf("%d", &t);
    if (t == 1) {
      int x;
      scanf("%d", &x);
      hp.push(x);
    } else if (t == 2)
      printf("%d\n", hp.top());
    else
      hp.pop();
  }
}
