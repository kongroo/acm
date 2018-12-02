#include <bits/stdc++.h>
using namespace std;


template <typename T> vector<int> manacher(const T &S) {
    int n = int(S.size());
    vector<int> F(n + n - 1, 1);
    for (int i = 1, x = 0; i < n + n - 1; i++) {
        F[i] = max(x + F[x] - i, 1 - (i & 1));
        if (x + x >= i) F[i] = min(F[i], F[x + x - i]);
        int a = (i - 1 - F[i]) >> 1, b = (i + 1 + F[i]) >> 1;
        while (a >= 0 && b < n && S[a] == S[b]) a--, b++, F[i] += 2;
        if (i + F[i] > x + F[x]) x = i;
    }
    return F;
}


// Codeforces. 1080E
const int N = 251;
int n, m;
char G[N][N];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%s", G[i] + 1);
    int ans = 0;
    for (int j1 = 1; j1 <= m; j1++) {
        vector<array<int, 26>> C(n);
        for (int j2 = j1; j2 <= m; j2++) {
            for (int i = 1; i <= n; i++) C[i - 1][G[i][j2] - 'a']++;
            for (int i = 0, j = 0; j <= n; j++) {
                if (j == n || count_if(C[j].begin(), C[j].end(), [](int x) { return x & 1; }) > 1) {
                    if (j > i)
                        for (auto x : manacher(decltype(C)(C.begin() + i, C.begin() + j))) ans += (x + 1) / 2;
                    i = j + 1;
                }
            }
        }
    }
    printf("%d\n", ans);
}
