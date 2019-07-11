#include <bits/stdc++.h>
using namespace std;

template <class T>
vector<T> reservior_sampling(const vector<T>& a, int k) {
  assert(k > 0 && k <= int(a.size()));
  vector<T> reservior(a.begin(), a.begin() + k);
  random_device rd;
  mt19937 gen(rd());
  for (int i = k; i < int(a.size()); i++) {
    int idx = uniform_int_distribution<int>(0, i)(gen);
    if (idx < k) reservior[idx] = a[i];
  }
  return reservior;
}

int main() {
  vector<int> a;
  for (int i = 0; i < 10000; i++) a.push_back(rand());
  auto b = reservior_sampling(a, 100);
  for (auto x : b) printf("%d\n", x);
}
