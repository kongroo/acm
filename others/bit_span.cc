#include <bits/stdc++.h>
using namespace std;

template <class T>
vector<T> xor_span(const vector<T>& a) {
  auto v = a;
  int k = 0;
  for (int i = 0; i < 8 * int(sizeof(T)); i++) {
    auto p = find_if(v.begin() + k, v.end(), [i](int x) { return x & 1 << i; });
    if (p == v.end()) continue;
    swap(v[k], *p);
    for (int j = 0; j < int(v.size()); j++)
      if (j != k && (v[j] & 1 << i)) v[j] ^= v[k];
    k++;
  }
  return v.resize(k), v;
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
