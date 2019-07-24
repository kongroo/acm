#include <bits/stdc++.h>
using namespace std;

// x = x0 + b / g * t, y = y0 - a / g * t
template <class T = int>
T exgcd(T a, T b, T& x, T& y) {
  if (!b) return x = 1, y = 0, a;
  T u = exgcd(b, a % b, y, x);
  return y -= a / b * x, u;
}

// solve ax + by = c
template <class T = int>
bool linear_equation(T a, T b, T c, T& x, T& y) {
  T g = exgcd(a, b, x, y);
  if (c % g) return false;
  x *= c / g, y *= c / g;
  return true;
}

// solve a * x % m = b
template <class T = int>
bool moduler_equation(T a, T b, T m, T& x) {
  long long r, s;
  T d = exgcd<long long>(a, m, r, s);
  if (b % d) return false;
  x = 1LL * b / d * r;
  x = (x % m + m) % m;
  return true;
}

template <class T = int>
T inv(T num, T m) {
  T x, y;
  exgcd(num, m, x, y);
  return (x + m) % m;
}

int main() { return 0; }
