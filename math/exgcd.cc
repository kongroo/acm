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

int main() { return 0; }
