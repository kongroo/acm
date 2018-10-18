#include <bits/stdc++.h>
using namespace std;

template <class T> T gcd(T x, T y) { return y == 0 ? x : gcd(y, x % y); }

// 拓展欧几里得
int exgcd(int a, int b, int& x, int& y) {
    if (!b) return x = 1, y = 0, a;
    int u = exgcd(b, a % b, y, x);
    return y -= a / b * x, u;
}


// 求解线性方程ax+by=c的一组解
bool equation(int a, int b, int c, int& x, int& y) {
    int g = exgcd(a, b, x, y);
    if (c % g) return false;
    x *= c / g;
    y *= c / g;
    return true;
}


// 求满足同余方程x%M[i]=R[i]的最小非负整数x，无解返回-1
int equation(const vector<int>& M, const vector<int>& R) {
    assert(M.size() == R.size());
    int ans = 0, lm = 1, x, y;
    for (int i = 0; i < (int)M.size(); i++) {
        int g = exgcd(lm, M[i], x, y);
        if ((R[i] - ans) % g || R[i] >= M[i]) return -1;
        x *= (R[i] - ans) / g;
        y = M[i] / g;
        ans += (x % y + y) % y * lm;
        ans %= lm *= y;
    }
    return ans;
}

