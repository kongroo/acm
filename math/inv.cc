#include <bits/stdc++.h>
using namespace std;

constexpr long long inv(long long x, long long m) {
  return x > m ? inv(x % m, m) : x > 1 ? inv(m % x, m) * (m - m / x) % m : x;
}

int main() { return 0; }
