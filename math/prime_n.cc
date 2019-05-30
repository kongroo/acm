#include <bits/stdc++.h>
using namespace std;

vector<int> prime_n(int n) {
  vector<int> Pr, L(n);
  L[1] = 1;
  for (int x = 2; x < n; x++) {
    if (!L[x]) Pr.push_back(L[x] = x);
    for (auto p : Pr) {
      if (x * p >= n) break;
      L[x * p] = p;
      if (x % p == 0) break;
    }
  }
  return Pr;
}

int main() { return 0; }
