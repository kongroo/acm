#include <bits/stdc++.h>
using namespace std;

template<int N> int maximum_clique(int G[N][N]) {
    int S[N][N] = {0}, F[N] = {0}, mx = 0;
    auto dfs = [&](int p, int num, auto f) -> void {
        if (p == 0) return void(mx = max(num, mx));
        for (int i = 0; i < p; i++) {
            int u = S[num][i], cnt = 0;
            if (p - i + num <= mx || F[u] + num <= mx) return;
            for (int j = i + 1; j < p; j++)
                if (G[u][S[num][j]]) S[num + 1][cnt++] = S[num][j];
            f(cnt, num + 1, f);
        }
    };
    for (int i = N - 1, cnt; cnt = 0, i >= 0; i--) {
        for (int j = i + 1; j < N; j++) if (G[i][j]) S[1][cnt++] = j;
        dfs(cnt, 1, dfs), F[i] = mx;
    }
    return mx;
}

// CF. 1105
const int N = 1e5 + 5, M = 45;
int n, m, idx = 1, G[M][M], S[M][M], F[M], mx = 0;
char buf[M];
unordered_map<string, int> Map;

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) for (int j = 1; j <= m; j++) G[i][j] = 1;
    vector<int> Idx;
    for (int i = 1, t; i <= n + 1; i++) {
        if (i <= n) scanf("%d", &t);
        else t = 1;
        if (i == 1) continue;
        if (t == 1) {
            for (auto x : Idx) for (auto y : Idx) G[x][y] = 0;
            Idx.clear();
        } else {
            scanf("%s", buf);
            string name = string(buf);
            if (!Map.count(name)) Map[name] = idx++;
            int id = Map[name];
            Idx.push_back(id);
        }
    }
    cout << maximum_clique(G) << endl;
}
