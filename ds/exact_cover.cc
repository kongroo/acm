#include <bits/stdc++.h>
using namespace std;


// r and c are 1-indexed
struct DLX {
    using PII = pair<int, int>;
    int n, m, sz;
    vector<int> V[6], S, &R, &U, &L, &D, &I, &J;
    DLX(int n, int m, vector<PII> P) : n(n), m(m), sz(0), S(m + 1),
        R(V[0]), U(V[1]), L(V[2]), D(V[3]), I(V[4]), J(V[5])  {
        assert(n > 0 && m > 0);
        sort(P.begin(), P.end());
        add({1, 0, m, 0, 0, 0});
        for (int i = 1; i <= m; i++) add({(i + 1) % (m + 1), i, i - 1, i, 0, i});
        sz = m + 1;
        vector<int> C(m + 1), F(n + 1);
        iota(C.begin(), C.end(), 0);
        for (auto p : P) {
            int r = p.first, c = p.second;
            assert(0 < r && r <= n && 0 < c && c <= m);
            if (!F[r]) add({sz, C[c], sz, c, r, c}), F[r] = sz;
            else add({F[r], C[c], sz - 1, c, r, c});
            L[R[sz]] = R[L[sz]] = U[D[sz]] = D[U[sz]] =  sz, C[c] = sz++, S[c]++;
        }
    }
    void add(const vector<int> &A) { for (int i = 0; i < 6; i++) V[i].push_back(A.at(i)); }
    void remove(int c) {
        L[R[c]] = L[c],  R[L[c]] = R[c];
        for (int i = D[c]; i != c; i = D[i])
            for (int j = R[i]; j != i; j = R[j])
                U[D[j]] = U[j], D[U[j]] = D[j], --S[J[j]];
    }
    void restore(int c) {
        for (int i = U[c]; i != c; i = U[i])
            for (int j = L[i]; j != i; j = L[j])
                U[D[j]] = D[U[j]] = j, ++S[J[j]];
        L[R[c]] = R[L[c]] = c;
    }
    vector<vector<int>> ans(int n_ans = 1, vector<int> Used = {}) {
        for (auto c : set<int>(Used.begin(), Used.end())) remove(c);
        vector<vector<int>> Ans;
        vector<int> Tmp;
        function<void()> dfs = [&]() {
            if (n_ans < 1) return;
            if (!R[0]) { n_ans--; Ans.emplace_back(Tmp); return ;}
            int c = R[0];
            for (int i = c; i; i = R[i]) if (S[i] < S[c]) c = i;
            remove(c);
            for (int i = D[c]; i != c; i = D[i]) {
                Tmp.push_back(I[i]);
                for (int j = R[i]; j != i; j = R[j]) remove(J[j]);
                dfs();
                if (n_ans < 1) return;
                Tmp.pop_back();
                for (int j = L[i]; j != i; j = L[j]) restore(J[j]);
            }
            restore(c);
        };
        dfs();
        return Ans;
    }
};


// 51Nod. 1211
int G[10][10];
int main() {
    for (int i = 1; i <= 9; i++)
        for (int j = 1; j <= 9; j++)
            scanf("%d", &G[i][j]);
    vector<pair<int, int>> P;
    auto row_col = [](int i, int k) { return 81 + (i - 1) * 9 + k; };
    auto col_col = [](int j, int k) { return 81 * 2 + (j - 1) * 9 + k; };
    auto block_col = [](int i, int j, int k) { return 81 * 3 + ((i - 1) / 3 * 3 + (j - 1) / 3) * 9 + k; };
    vector<int> Used;
    int cnt = 0;
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            cnt += !!G[i][j];
            for (int k = 1; k <= 9; k++) {
                int r = (i - 1) * 81 + (j - 1) * 9 + k;
                int a = (i - 1) * 9 + j, b = row_col(i, k), c = col_col(j, k), d = block_col(i, j, k);
                for (auto x : {a, b, c, d}) P.emplace_back(r, x);
                if (k == G[i][j]) for (auto x : {a, b, c, d}) Used.push_back(x);
            }
        }
    }
    if (cnt < 17) return puts("No Solution"), 0;
    DLX dlx(9 * 9 * 9, 9 * 9 * 4, P);
    auto Ans = dlx.ans(2, Used);
    if (Ans.size() != 1u) printf("No Solution\n");
    else {
        for (auto r : Ans.front()) {
            r--;
            int k = r % 9 + 1;
            r /= 9;
            int j = r % 9 + 1;
            r /= 9;
            int i = r % 9 + 1;
            G[i][j] = k;
        }
        for (int i = 1; i <= 9; i++)
            for (int j = 1; j <= 9; j++)
                printf("%d%c", G[i][j], " \n"[j == 9]);
    }
    return 0;
}
