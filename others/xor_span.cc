#include <bits/stdc++.h>
using namespace std;

template <class T> vector<T> xor_span(vector<T> a) {
  int k = 0;
  for (int i = 8 * int(sizeof(T)) - 1; i >= 0; --i) {
    auto p = find_if(a.begin() + k, a.end(), [i](T x) { return x >> i & T(1); });
    if (p == a.end()) continue;
    swap(a[k], *p);
    for (int j = 0; j < int(a.size()); j++)
      if (j != k && (a[j] & T(1) << i)) a[j] ^= a[k];
    k++;
  }
  return a.resize(k), a;
}

// CF. 1101G
const int N = 2e5 + 5;
int n, a[N];

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  vector<int> b;
  for (int i = 1, cur = 0; i <= n; i++) {
    cur ^= a[i];
    if (i == n && !cur) return puts("-1"), 0;
    b.push_back(cur);
  }
  auto v = xor_span(b);
  cout << v.size() << endl;
}
