#include <bits/stdc++.h>
using namespace std;


// x % M[i] = A[i], M[i] coprime
long long crt(const vector<int>& A, const vector<int>& M) {
    assert(A.size() == M.size());
    function<int(int, int)> inv = [&](int x, int p) {
        return x > 1 ? inv(p % x, p) * 1LL * (p - p / x) % p : x;
    };
    auto m = 1LL, ans = 0LL;
    for (auto x : M) m *= x;
    for (size_t i = 0; i < A.size(); i++)
        ans = (ans + A[i] * m / M[i] * inv(m / M[i] % M[i], M[i])) % m;
    return ans;
}


// 51Nod. 1079
int main() {
    int n;
    scanf("%d", &n);
    vector<int> A, M;
    for (int i = 0; i < n; i++) {
        int p, a;
        scanf("%d%d", &p, &a);
        A.push_back(a), M.push_back(p);
    }
    printf("%d", (int)crt(A, M));
    return 0;
}
