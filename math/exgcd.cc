#include <bits/stdc++.h>
using namespace std;


int exgcd(int a, int b, int& x, int& y) {
    if (!b) return x = 1, y = 0, a;
    int u = exgcd(b, a % b, y, x);
    return y -= a / b * x, u;
}


// solve ax + by = c
bool linear_equation(int a, int b, int c, int& x, int& y) {
    int g = exgcd(a, b, x, y);
    if (c % g) return false;
    x *= c / g, y *= c / g;
    return true;
}


int main() {
    return 0;
}
