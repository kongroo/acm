#include <bits/stdc++.h>
using namespace std;

template <class T>
void knuth_durstenfeld_shuffle(vector<T>& a) {
  random_device rd;
  mt19937 gen(rd());
  for (int i = int(a.size()) - 1; i >= 0; i--) swap(a[uniform_int_distribution<>(0, i)(gen)], a[i]);
}

int main() {
  vector<int> a;
  for (int i = 0; i < 100; i++) a.push_back(i);
  knuth_durstenfeld_shuffle(a);
  for (auto x : a) printf("%d\n", x);
}
