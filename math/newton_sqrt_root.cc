#include <bits/stdc++.h>
using namespace std;

// updating: x[i+1] = x[i] - f(x[i]) / f'(x[i])
double sqrt_newton(double n, double eps = 1e-15) {
  double x = 1;
  for (double nx;; x = nx) {
    nx = (x + n / x) / 2;
    if (abs(x - nx) < eps) break;
  }
  return x;
}

int main() { cout << sqrt_newton(3.6) << endl; }
