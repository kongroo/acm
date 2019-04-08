## strings/hash_1.cc

```c++
#include <bits/stdc++.h>
using namespace std;


struct Hash1 {
    int n, p, m;
    vector<int> P, H;
    template <typename T> Hash1(const T &S, int p = 131, int m = 1000000409) :
        n(S.size()), p(p), m(m), P(n), H(n + 1) {
        P[0] = 1, H[n] = 0;
        for (int i = 1; i < n; i++) P[i] = 1LL * P[i - 1] * p % m;
        for (int i = n - 1; i >= 0; i--) H[i] = (1LL * p * H[i + 1] % m + S[i]) % m;
    }
    int get(int l, int r) { return (H[l] - 1LL * H[r] * P[r - l] % m + m) % m;}
};


// CF. 126B
int main() {
    string s;
    cin >> s;
    Hash1 hs(s);
    int n = s.size();
    auto fail = []() { return puts("Just a legend"), 0; };
    if (n < 3) return fail();
    auto check = [&](int len) {
        auto t = hs.get(0, len);
        for (int i = 1; i < n - len; i++) {
            if (hs.get(i, i + len) == t) return true;
        }
        return false;
    };
    vector<int> L;
    for (int len = 1; len < n - 1; len++) {
        int l = 0, r = n - len;
        auto t = hs.get(l, l + len), u = hs.get(r, r + len);
        if (t == u) L.push_back(len);
    }
    int l = 0, r = (int)L.size();
    if (r == 0 || !check(L[0])) return fail();
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (check(L[m])) l = m;
        else r = m;
    }
    cout << s.substr(0, L[l]) << endl;
    return 0;
}
```

## strings/p_function.cc

```c++
#include <bits/stdc++.h>
using namespace std;


// P[0] = 0, P[i] is the length of longest proper prefix 
// of S[0...i] that is also a suffix of it
template <typename T> vector<int> get_p(const T &S) {
    vector<int> P(S.size());
    for (int l = 0, r = 1; r < (int)S.size(); r++) {
        while (l && S[l] != S[r]) l = P[l - 1];
        if (S[l] == S[r]) P[r] = ++l;
    }
    return P;
}



// 51Nod. 1277
int main() {
    string s;
    cin >> s;
    int n = s.size();
    auto P = get_p(s);
    vector<int> F(n);
    for (int i = n - 1; i >= 0; i--) {
        F[i]++;
        int t = P[i] - 1;
        if (t < 0) continue;
        F[t] += F[i];
    }
    auto ans = 0LL;
    for (int i = 0; i < n; i++) ans = max(ans, 1LL * F[i] * (i + 1));
    cout << ans << endl;
    return 0;
}
```

## strings/aho_corasick.cc

```c++
#include <bits/stdc++.h>
using namespace std;


template <int N = 26, int B = 'a', typename T = int> struct AhoCorasick {
    struct State { int link; T v; array<int, N> M; };
    vector<State> D;
    function<T(T, T)> op;
    bool built;
    AhoCorasick(function<T(T, T)> op = plus<T>()) : D(2), op(op), built(false) {}
    template <typename Seq> void insert(const Seq &S, T fin, T mid = T(), int t = 1) {
        for (auto c : S) {
            c -= B, assert(0 <= c && c < N);
            if (!D[t].M[c]) D[t].M[c] = D.size(), D.emplace_back(D[0]);
            D[t].v = op(D[t].v, mid), t = D[t].M[c];
        }
        D[t].v = op(D[t].v, fin), built = false;
    }
    void build_fail() {
        queue<int> Q;
        Q.push(1), built = true;
        while (!Q.empty()) {
            int t = Q.front();
            Q.pop();
            for (int c = 0; c < N; c++) if (D[t].M[c]) {
                    int nxt = D[t].M[c], u = D[t].link;
                    while (u && !D[u].M[c]) u = D[u].link;
                    D[nxt].link = u ? D[u].M[c] : 1, Q.push(nxt);
                }
        }
    }
    template <typename R, typename Seq>
    R calc(const Seq &S,  function<void(R &, T)> al, const R &init = R()) {
        if (!built) build_fail();
        R ans(init);
        int t = 1, tt;
        for (auto c : S) {
            c -= B, assert(0 <= c && c < N);
            while (t && !D[t].M[c]) t = D[t].link;
            t = t ? D[t].M[c] : 1, tt = t;
            while (tt) al(ans, D[tt].v), tt = D[tt].link;
        }
        return ans;
    }
};


// Luogu. 3796
int main() {
    ios::sync_with_stdio(0);
    int n;
    while (cin >> n && n) {
        AhoCorasick<> ac([](int x, int y) { return y; });
        vector<string> V(n + 1);
        for (int i = 1; i <= n; i++) cin >> V[i];
        for (int i = 1; i <= n; i++) ac.insert(V[i], i);
        string s;
        cin >> s;
        vector<int> Tmp(n + 1);
        auto Cnt = ac.calc<vector<int>>(s, [](vector<int> &x, int y) { x[y]++; }, vector<int>(n + 1));
        int m = *max_element(Cnt.begin() + 1, Cnt.end());
        cout << m << endl;
        for (int i = 1; i <= n; i++) if (Cnt[i] == m) cout << V[i] << endl;
    }
}
```

## strings/hash_2.cc

```c++
#include <bits/stdc++.h>
using namespace std;


struct Hash2 {
    int n, p1, p2, m1, m2;
    vector<int> H[4];
    constexpr int mul(int x, int y, int m) { return 1LL * x * y % m; }
    constexpr int add(int x, int y, int m) { int t = x + y; return t < 0 ? t + m : t < m ? t : t - m; }
    template <typename T> Hash2(const T &S, int p1 = 131, int p2 = 1313, int m1 = 1e9 + 7,
                                int m2 = 1e9 + 9): n(S.size()), p1(p1), p2(p2), m1(m1), m2(m2) {
        for (int i = 0; i < 4; i++) H[i].assign(n + 1, 0ULL);
        H[2][0] = H[3][0] = 1;
        for (int i = 1; i < n; i++) H[2][i] = mul(H[2][i - 1], p1, m1), H[3][i] = mul(H[3][i - 1], p2, m2);
        for (int i = n - 1; i >= 0; i--) {
            H[0][i] = add(mul(H[0][i + 1], p1, m1), S[i], m1);
            H[1][i] = add(mul(H[1][i + 1], p2, m2), S[i], m2);
        }
    }
    pair<int, int> get(int l, int r) {
        return {
            add(H[0][l], -mul(H[0][r], H[2][r - l], m1), m1),
            add(H[1][l], -mul(H[1][r], H[3][r - l], m2), m2)
        };
    }
};


// CF. 126B
int main() {
    string s;
    cin >> s;
    Hash2 hs(s);
    int n = s.size();
    auto fail = []() { return puts("Just a legend"), 0; };
    if (n < 3) return fail();
    auto check = [&](int len) {
        auto t = hs.get(0, len);
        for (int i = 1; i < n - len; i++) {
            if (hs.get(i, i + len) == t) return true;
        }
        return false;
    };
    vector<int> L;
    for (int len = 1; len < n - 1; len++) {
        int l = 0, r = n - len;
        auto t = hs.get(l, l + len), u = hs.get(r, r + len);
        if (t == u) L.push_back(len);
    }
    int l = 0, r = (int)L.size();
    if (r == 0 || !check(L[0])) return fail();
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (check(L[m])) l = m;
        else r = m;
    }
    cout << s.substr(0, L[l]) << endl;
    return 0;
}
```

## strings/expression.cc

```c++
#include <bits/stdc++.h>
using namespace std;


template <typename T> T expression(const string& S, int l = 0, int r = -1) {
    static const vector<unordered_map<char, function<T(T, T)>>> Table = {
        { {'+', plus<T>() }, {'-', minus<T>() } },
        { {'*', multiplies<T>()}, {'/', divides<T>()} }
    };
    if (r == -1) r = int(S.size());
    if (l >= r) return T();
    if (S[l] == ' ') return expression<T>(S, l + 1, r);
    if (S[r - 1] == ' ') return expression<T>(S, l, r - 1);
    for (auto& M : Table) {
        int p = -1;
        for (int i = l, d = 0, f = 0; i < r; i++) {
            int c = S[i];
            if (isspace(c)) continue;
            d += c == '(' ? 1 : c == ')' ? -1 : 0;
            if (f && d == 0 && M.count(c)) p = i;
            f = isdigit(c) || c == '.' || c == ')';
        }
        if (p != -1) return M.at(S[p])(expression<T>(S, l, p), expression<T>(S, p + 1, r));
    }
    if (S[l] == '(' && S[r - 1] == ')') return expression<T>(S, l + 1, r - 1);
    return T(stod(S.substr(l, r - l)));
}


int main() {
    vector<string> E = {
        "-2 * -3",
        "1.0",
        "1000 * 1000",
        "2 / 5",
        "( 562  - 2.51 ) / ( -643 + 2 * 56.3 ) ",
        " 3 * -2.0" // This is not valid
    };
    for (auto& s : E) cout << s << " = " << expression<double>(s) << endl;
    return 0;
}
```

## strings/weight_hash.cc

```c++
#include <bits/stdc++.h>
using namespace std;


// works for [0, n)
struct HashW {
    using ULL = unsigned long long;
    vector<ULL> P;
    HashW(int n): P(n, 1313131313) { for (int i = 1; i < n; i++) P[i] *= P[i - 1]; }
    template <typename T> ULL get(const T &S) { ULL r(0); for (auto c : S) r += P[c]; return r; }
};


// CF. 154C
int main() {
    using PII = pair<int, int>;
    int n, m;
    scanf("%d%d", &n, &m);
    HashW hs(n + 1);
    vector<vector<int>> G(n + 1);
    vector<PII> E;
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
        E.emplace_back(u, v);
    }
    for (int i = 1; i <= n; i++) {
        sort(G[i].begin(), G[i].end());
    }
    unordered_map<long long, int>  M;
    for (int i = 1; i <= n; i++) M[hs.get(G[i])]++;
    auto ans = 0LL;
    for (auto p : M) {
        int t = p.second;
        ans += 1LL * t * (t - 1) / 2;
    }
    for (auto p : E) {
        int u, v;
        tie(u, v) = p;
        if (!binary_search(G[u].begin(), G[u].end(), u))
            G[u].push_back(u), sort(G[u].begin(), G[u].end());
        if (!binary_search(G[v].begin(), G[v].end(), v))
            G[v].push_back(v), sort(G[v].begin(), G[v].end());
        if (G[u] == G[v]) ans++;
    }
    printf("%lld\n", ans);
    return 0;
}
```

## strings/bkdr_hash.cc

```c++
#include <bits/stdc++.h>
using namespace std;


template <typename T> constexpr auto bkdr_hash(const T& S) {
    auto res1 = 0ULL, res2 = 0ULL, seed1 = 131ULL, seed2 = 1313ULL;
    for (auto c : S) res1 = res1 * seed1 + c, res2 = res2 * seed2 + c;
    return res1 * res2;
}


// CF. 154C
int main() {
    using ULL = unsigned long long;
    using PII = pair<int, int>;
    int n, m;
    scanf("%d%d", &n, &m);
    vector<vector<int>> G(n + 1);
    vector<PII> E;
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
        E.emplace_back(u, v);
    }
    for (int i = 1; i <= n; i++) {
        sort(G[i].begin(), G[i].end());
    }
    unordered_map<ULL, int>  M;
    for (int i = 1; i <= n; i++) M[bkdr_hash(G[i])]++;
    auto ans = 0LL;
    for (auto p : M) {
        int t = p.second;
        ans += 1LL * t * (t - 1) / 2;
    }
    for (auto p : E) {
        int u, v;
        tie(u, v) = p;
        if (!binary_search(G[u].begin(), G[u].end(), u))
            G[u].push_back(u), sort(G[u].begin(), G[u].end());
        if (!binary_search(G[v].begin(), G[v].end(), v))
            G[v].push_back(v), sort(G[v].begin(), G[v].end());
        if (G[u] == G[v]) ans++;
    }
    printf("%lld\n", ans);
    return 0;
}
```

## strings/manacher.cc

```c++
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
```

## strings/z_function.cc

```c++
#include <bits/stdc++.h>
using namespace std;

// Z[0] = 0, Z[i] is max that let s[0..Z[i]-1] == s[i..i+Z[i]-1]
template <typename T> vector<int> get_z(const T& s) {
    int n = int(s.size());
    vector<int> Z(n);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) Z[i] = min(r - i, Z[i - l]);
        while (i + Z[i] < n && s[i + Z[i]] == s[Z[i]]) Z[i]++;
        if (r <= i + Z[i]) l = i, r = i + Z[i];
    }
    return Z;
}



// CF. 1051E
int main() {
    using LL = long long;
    const int Mod = 998244353;
    const int N = 1e6 + 5;
    vector<LL> F(N), S(N);
    string a, l, r;
    cin >> a >> l >> r;
    int n = a.size();
    F[n] = S[n] = 1;
    auto Z1 = get_z(l + "#" + a);
    auto Z2 = get_z(r + "#" + a);
    int lenL = int(l.length()), lenR = int(r.length());
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] == '0') {
            if (l == "0") F[i] = F[i + 1];
            else F[i] = 0;
        } else {
            if (lenR == 1 && r < a.substr(i, 1)) return !printf("0\n");
            int x = i + lenL - 1, y = i + lenR - 1;
            x = min(x, n), y = min(y, n);
            if (x < n) {
                int pos = Z1[lenL + 1 + i];
                if (pos < lenL && a[i + pos] < l[pos]) x++;
            }
            if (y < n) {
                int pos = Z2[lenR + 1 + i];
                if (pos < lenR && r[pos] < a[i + pos]) y--;
            }
            F[i] = (S[x + 1] - S[y + 2] + Mod) % Mod;
        }
        S[i] = (S[i + 1] + F[i]) % Mod;
    }
    cout << F[0] << endl;
    return 0;
}
```

## strings/p_trie.cc

```c++
#include <bits/stdc++.h>
using namespace std;


// Persistent Trie
template <int N = 26, int B = 'a', typename T = int> struct PTrie {
    int n;
    vector<array<int, N>> D;
    vector<T> V;
    vector<int> Rt;
    function<T(T, T)> al;
    PTrie(function<T(T, T)> al = plus<T>()): n(1), D(1), V(1), Rt(1, 0), al(al) {}

    template <typename Seq> void insert(const Seq &S, T x, T m = T()) {
        static const auto ins_ = [&](int o, size_t i, auto f) -> int {
            int no = n++, tmp;
            D.emplace_back(D[o]), V.push_back(V[o]);
            V[no] = al(V[no], i == S.size() ? x : m);
            if (i < S.size())  { tmp = f(D[no].at(S[i] - B), i + 1, f), D[no][S[i] - B] = tmp; }
            return no;
        };
        Rt.push_back(ins_(Rt.back(), 0, ins_));
    }
    template <typename Seq> pair<bool, T> query(const Seq &S, int t = -1) {
        int u = t < 0 ? Rt.back() : Rt.at(t);
        for (auto x : S) { u = D[u][x - B]; if (!u) return {false, T()}; }
        return {true, V[u]};
    }
};


// 51Nod. 1295
PTrie<2, '0', int> tr;
string query(int l, int r, const string &S, size_t i) {
    if (i == S.size()) return "";
    int d = 1 - S[i] + '0';
    int sum = tr.V[tr.D[r][d]] - tr.V[tr.D[l][d]];
    if (sum > 0) return "1" + query(tr.D[l][d], tr.D[r][d], S, i + 1);
    else return "0" + query(tr.D[l][1 - d], tr.D[r][1 - d], S, i + 1);
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    auto tostr = [](int x) { return bitset<32>(x).to_string(); };
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        tr.insert(tostr(x), 1, 1);
    }
    while (q--) {
        int x, l, r;
        scanf("%d%d%d", &x, &l, &r);
        l++, r++;
        auto S = query(tr.Rt[l - 1], tr.Rt[r], tostr(x), 0);
        printf("%d\n", stoi(S, NULL, 2));
    }
    return 0;
}
```

## strings/sa.cc

```c++
#include <bits/stdc++.h>
using namespace std;

template <typename T> vector<int> build_sa(const T &S, vector<int> &Sa, vector<int> &H) {
    int n = (int)S.size();
    vector<int> R(S.begin(), S.end()), U;
    Sa.resize(n + 1), iota(Sa.begin(), Sa.end(), 0), R.push_back(INT_MIN);
    for (int len = 1; len <= n; len <<= 1, R = U) {
        auto cmp = [&](int i, int j) {
            return R[i] != R[j] ? R[i] < R[j] :
                   (i + len < n ? R[i + len] : 0) < (j + len < n ? R[j + len] : 0);
        };
        sort(Sa.begin(), Sa.end(), cmp), U = R, U[Sa[0]] = 0;
        for (int i = 1; i <= n; i++) U[Sa[i]] = U[Sa[i - 1]] + cmp(Sa[i - 1], Sa[i]);
    }
    H.resize(n + 1), H[0] = R.back() = 0;
    for (int i = 0, h = 0; i < n; H[R[i++] - 1] = h, h -= h > 0)
        for (int j = Sa[R[i] - 1]; j + h < n && i + h < n; h++) if (S[j + h] != S[i + h]) break;
    return R;
}

// CF. 873F
int main() {
    using LL = long long;
    int n;
    scanf("%d", &n);
    string s, t;
    cin >> s >> t;
    reverse(s.begin(), s.end());
    reverse(t.begin(), t.end());
    vector<int> Sa, H;
    build_sa(s, Sa, H);
    vector<int> Cnt(n + 1);
    for (int i = 1; i <= n; i++) Cnt[i] = (i == 0 ? 0 : Cnt[i - 1]) + int(t[Sa[i]] == '1');
    stack<int> S;
    LL ans = 0;
    for (int i = 0; i < n; i++) if (t[i] == '0') {
            ans = n - i;
            break;
        }
    for (int i = 0; i <= n; i++) {
        while (!S.empty() && H[S.top()] > H[i]) {
            int t = S.top();
            S.pop();
            int r = i;
            int l = S.empty() ? 1 : S.top() + 1;
            LL len = r - l + 1 - (Cnt[r] - (l == 0 ? 0 : Cnt[l - 1]));
            if (len == 1) continue;
            LL cur = H[t] * len;
            ans = max(ans, cur);
        }
        S.push(i);
    }
    cout << ans << endl;
    return 0;
}
```

## strings/trie.cc

```c++
#include <bits/stdc++.h>
using namespace std;


template <int N = 26, int B = 'a', class T = int> struct Trie {
    struct State { bool ini = true, fin = false; T v; array<int, N> M; };
    vector<State> D;
    function<T(T, T)> op;
    Trie(function<T(T, T)> op = plus<T>()): D(2), op(op) {}

    template <typename Seq> void insert(const Seq &S, T fin, T mid = T(), int t = 1) {
        for (auto c : S) {
            c -= B, assert(0 <= c && c < N);
            if (!D[t].M[c]) D[t].M[c] = D.size(), D.emplace_back(D[0]);
            D[t].v = exchange(D[t].ini, false) ? mid : op(D[t].v, mid), t = D[t].M[c];
        }
        D[t].v = exchange(D[t].ini, false) ? fin : op(D[t].v, fin), D[t].fin = true;
    }
    template <typename Seq> pair<int, T> query(const Seq &S, int t = 1) {
        for (auto x : S) { t = D[t].M.at(x - B); if (!t) return {0, T()}; }
        return {t, D[t].v};
    }
};



// Luogu.2580
int main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    Trie<> tr;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        tr.insert(s, i);
    }
    int q;
    cin >> q;
    bitset<10005> B;
    while (q--) {
        string s;
        cin >> s;
        auto p = tr.query(s);
        if (!p.first || !p.second) cout << "WRONG\n";
        else if (B.test(p.second)) cout << "REPEAT\n";
        else cout << "OK\n", B.set(p.second);
    }
    return 0;
}
```

## strings/suffix_automaton.cc

```c++
#include <bits/stdc++.h>
using namespace std;


template <int N = 26, int B = 'a'> struct SuffixAutomaton {
    struct State { int len = 0, link = 0; array<int, N> M; };
    int last = 1;
    vector<State> D;
    template <typename X> SuffixAutomaton(const X &Seq) : D(2) { for (auto c : Seq) insert(c); }
    void insert(int c) {
        c -= B, assert(0 <= c && c < N);
        int cur = D.size(), p = last;
        D.emplace_back(D[0]), D[cur].len = D[last].len + 1;
        while (p && !D[p].M[c]) D[p].M[c] = cur, p = D[p].link;
        if (!p) D[cur].link = 1;
        else {
            int q = D[p].M[c];
            if (D[q].len == D[p].len + 1) D[cur].link = q;
            else {
                int clone = D.size();
                D.emplace_back(D[q]), D[clone].len = D[p].len + 1;
                while (p && D[p].M[c] == q) D[p].M[c] = clone, p = D[p].link;
                D[q].link = D[cur].link = clone;
            }
        }
        last = cur;
    }
    template <typename Seq> int find(const Seq &S, int t = 1) {
        for (auto c : S) { t = D[t].M.at(c - B); if (!t) return 0; }
        return t;
    }
    template <typename Seq> Seq lcs(const Seq &S, int t = 1) {
        int len = 0, mlen = 0, pos = 0;
        for (size_t i = 0; i < S.size(); i++) {
            int c = S[i] - B;
            while (t > 1 && !D[t].M.at(c)) t = D[t].link, len = D[t].len;
            if (D[t].M.at(c)) t = D[t].M[c], len++;
            if (len > mlen) mlen = len, pos = i;
        }
        return Seq(S.begin() + pos - mlen + 1, S.begin() + pos + 1);
    }
    vector<int> get_counts() {
        vector<int> F(D.size());
        auto dp = [&](int u, auto f) -> int {
            if (F[u]) return F[u];
            for (int i = 0; i < N; i++) if (D[u].M[i]) F[u] += f(D[u].M[i], f);
            return ++F[u];
        };
        for (size_t i = 1; i < F.size(); i++) F[i] = dp(i, dp);
        return F;
    }
};


// Spoj. SUBLEX
int main() {
    ios::sync_with_stdio(0);
    string s;
    cin >> s;
    SuffixAutomaton<> sa(s);
    auto F = sa.get_counts();
    int q;
    cin >> q;
    while (q--) {
        int k, cnt = 0, u = 1;
        cin >> k;
        k++;
        string t;
        while (cnt < k) {
            int v = 0;
            cnt++;
            if (cnt == k) break;
            for (int i = 0; i < 26; i++) {
                v = sa.D[u].M[i];
                if (!v) continue;
                cnt += F[v];
                if (cnt >= k) {
                    cnt -= F[v];
                    t.push_back(i + 'a');
                    break;
                }
            }
            u = v;
            if (!u) break;
        }
        cout << t << endl;
    }
}
```

## basic/sortings.cc

```c++
#include <bits/stdc++.h>
using namespace std;


template <class It, class Cmp>
void bubble_sort(It l, It r, Cmp cmp) {
    for (It u = r; u > l; --u)
        for (It i = l; i < u; ++i)
            if (cmp(*(i + 1), *i)) swap(*i, *(i + 1));
}
template <class It> void bubble_sort(It l, It r) {
    bubble_sort(l, r, less<decltype(*l)>());
}


template <class It, class Cmp>
void selection_sort(It l, It r, Cmp cmp) {
    for (It u = l; u < r; ++u)
        for (It i = u + 1; i < r; ++i)
            if (cmp(*i, *u)) swap(*i, *u);
}
template <class It> void selection_sort(It l, It r) {
    selection_sort(l, r, less<decltype(*l)>());
}


template <class It, class Cmp>
void insertion_sort(It l, It r, Cmp cmp) {
    for (It u = l; u < r; ++u)
        for (It i = u; i > l && cmp(*i, *(i - 1)); --i)
            swap(*i, *(i - 1));
}
template <class It> void insertion_sort(It l, It r) {
    insertion_sort(l, r, less<decltype(*l)>());
}


template <class It, class Cmp>
void merge_sort(It l, It r, Cmp cmp) {
    if (distance(l, r) < 2) return;
    It m = l + distance(l, r) / 2;
    merge_sort(l, m, cmp), merge_sort(m, r, cmp);
    inplace_merge(l, m, r, cmp);
}
template <class It> void merge_sort(It l, It r) {
    merge_sort(l, r, less<decltype(*l)>());
}


template <class It, class Cmp>
void quick_sort(It l, It r, Cmp cmp) {
    if (distance(l, r) < 2) return;
    if (distance(l, r) <= 20) return insertion_sort(l, r, cmp);
    const auto &a = *l, &b = *(r - 1), &c = *(l + distance(l, r) / 2);
    auto pivot = max(min(a, b, cmp), min(max(a, b, cmp), c, cmp), cmp);
    It u = l, v  = r;
    for (It i = u; i < v; ++i, i = max(i, u))
        if (cmp(*i, pivot)) swap(*i--, *u++);
        else if (cmp(pivot, *i)) swap(*i--, *--v);
    quick_sort(l, u, cmp), quick_sort(v, r, cmp);
}
template <class It> void quick_sort(It l, It r) {
    quick_sort(l, r, less<decltype(*l)>());
}


int main() {
    int n;
    scanf("%d", &n);
    vector<int> A(n);
    for (int i = 0; i < n; i++) scanf("%d", &A[i]);
    quick_sort(A.begin(), A.end());
    for (int i = 0; i < n; i++) printf("%d%c", A[i], " \n"[i + 1 == n]);
}
```

## basic/heap.cc

```c++
#include <bits/stdc++.h>
using namespace std;


template <typename T> struct Heap {
    vector<T> D;
    function<bool(T, T)> cmp;
    Heap(function<bool(T, T)> cmp = less<T>()): D(1), cmp(cmp) {}

    void push(const T &x) {
        D.emplace_back(x);
        for (int t = D.size() - 1; t > 1; t >>= 1)
            if (cmp(D[t], D[t >> 1])) swap(D[t], D[t >> 1]);
    }
    const T top() const { return D[1]; }
    void pop() {
        swap(D.at(1), D.back()), D.pop_back();
        for (size_t t = 1;;) {
            bool b1 = (t << 1) < D.size() && cmp(D[t << 1], D[t]);
            bool b2 = (t << 1 | 1) < D.size() && cmp(D[t << 1 | 1], D[t])
                      && cmp(D[t << 1 | 1], D[t << 1]);
            if (!b1 && !b2) break;
            else if (b2) swap(D[t], D[t << 1 | 1]), t = t << 1 | 1;
            else swap(D[t], D[t << 1]), t <<= 1;
        }
    }
};


// Luogu. 3378
int main() {
    int n;
    scanf("%d", &n);
    Heap<int> hp;
    for (int i = 0; i < n; i++) {
        int t;
        scanf("%d", &t);
        if (t == 1) {
            int x;
            scanf("%d", &x);
            hp.push(x);
        } else if (t == 2) printf("%d\n", hp.top());
        else hp.pop();
    }
}
```

## math/primality.cc

```c++
#include <bits/stdc++.h>
using namespace std;


namespace Primality {
using LL = long long;
constexpr LL mmul(LL x, LL y, LL m) {
    LL ret = x * y - (LL)((long double)x * y / m + 0.5) * m;
    return ret < 0 ? ret + m : ret;
}
constexpr LL mpow(LL x, LL y, LL m) {
    LL s = 1;
    for (LL c = x % m; y; c = mmul(c, c, m), y >>= 1)
        if (y & 1) s = mmul(s, c, m);
    return s;
}
constexpr bool miller_rabin(LL num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (~num & 1) return false;
    const int u[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022, 0};
    LL e = num - 1, a = 0, c = 0;
    while (~e & 1) e /= 2, c++;
    for (int i = 0; u[i]; i++) {
        if (num <= u[i]) return true;
        a = mpow(u[i], e, num);
        if (a == 1) continue;
        for (int j = 1; a != num - 1; j++) {
            if (j == c) return false;
            a = mmul(a, a, num);
        }
    }
    return true;
}
LL pollard_rho(LL n) {
    if (n <= 3 || miller_rabin(n)) return n;
    for (;;) {
        int i = 1, cnt = 2;
        LL x = rand() % n, y = x, c = rand() % n;
        if (!c || c == n - 2) c++;
        do {
            LL u = __gcd(n - x + y, n);
            if (u > 1 && u < n) return u;
            if (++i == cnt) y = x, cnt *= 2;
            x = (c + mmul(x, x, n)) % n;
        } while (x != y);
    }
    return n;
}
vector<LL> factorize(LL n) {
    vector<LL> u;
    for (auto x : {2, 3, 5, 7, 11, 13}) {
        while (n % x == 0) n /= x, u.push_back(x);
    }
    if (n > 1) u.push_back(n);
    for (size_t i = u.size() - 1; i < u.size(); i++) {
        LL x = pollard_rho(u[i]);
        if (x == u[i]) continue;
        u[i--] /= x;
        u.push_back(x);
    }
    sort(u.begin(), u.end());
    return u;
}
};


int main() {
    cout << Primality::miller_rabin(1e9 + 7) << endl;
    return 0;
}
```

## math/josephus.cc

```c++
#include<bits/stdc++.h>
using namespace std;


// no. 0 to n-1
int josephus(int n, int k) {
    int s = 0;
    for (int i = 2; i <= n; i++) s = (s + k) % i;
    return s;
}


// 51Nod. 1073
int main() {
    int n, k;
    cin >> n >> k;
    cout << josephus(n, k) + 1 << endl;
    return 0;
}
```

## math/d_func.cc

```c++
#include <bits/stdc++.h>
using namespace std;


// Cnt of divisors, partial multiplicative function
constexpr int d_func(long long n) {
    int ret = 1;
    for (auto i = 2LL; i * i <= n; i++) {
        if (n % i == 0) {
            int cnt = 0;
            while (n % i == 0) n /= i, cnt++;
            ret *= cnt + 1;
        }
    }
    return n > 1 ? ret * 2 : ret;
}


// Spoj. COMDIV
int main() {
    int T;
    cin >> T;
    while (T--) {
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%d\n", d_func(__gcd(a, b)));
    }
}
```

## math/crt.cc

```c++
#include <bits/stdc++.h>
using namespace std;


// x % M[i] = A[i], M[i] coprime
long long crt(const vector<int> &A, const vector<int> &M) {
    assert(A.size() == M.size());
    auto inv = [&](int x, int p, auto inv) constexpr -> int {
        return  x > p ? inv(x % p, p, inv) : x > 1 ? inv(p % x, p, inv) * 1LL * (p - p / x) % p : x;
    };
    auto m = 1LL, ans = 0LL;
    for (auto x : M) m *= x;
    for (size_t i = 0; i < A.size(); i++)
        ans = (ans + A[i] * m / M[i] * inv(m / M[i] % M[i], M[i], inv)) % m;
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
    printf("%d\n", (int)crt(A, M));
    return 0;
}
```

## math/inv_n.cc

```c++
#include <bits/stdc++.h>
using namespace std;


// m must be prime
vector<int> inv_n(int n, int m = 1e9 + 7) {
    vector<int> Inv(n, 1);
    for (int x = 2; x < n; x++) Inv[x] = Inv[m % x] * 1LL * (m - m / x) % m;
    return Inv;
}


int main() {
    return 0;
}
```

## math/fft_mod.cc

```c++
#include <bits/stdc++.h>
using namespace std;


namespace MFFT {
static const double PI = acos(-1.0);
template <typename T> void arrange(vector<T> &A) {
    int n = A.size();
    assert(n == (n & -n));
    for (int i = 1, x = 0, y = 0; i <= n; i++) {
        if (x > y) swap(A[x], A[y]);
        x ^= i & -i, y ^= n / (i & -i) >> 1;
    }
}
template <typename T> void fourier(vector<complex<T>> &A, int inv) {
    assert((inv == 1 || inv == -1) && is_floating_point<T>::value);
    int n = 1 << (32 - __builtin_clz(A.size() - 1));
    A.resize(n), arrange(A);
    vector<complex<T>> W(n >> 1, {1, 0});
    for (int l = 1; l < n; l <<= 1) {
        complex<T> wl(cos(inv * PI / l), sin(inv * PI / l)), t;
        for (int i = l - 2; i >= 0; i -= 2) W[i] = W[i >> 1];
        for (int i = 1; i < l; i += 2) W[i] = W[i - 1] * wl;
        for (int i = 0; i < l; i++)
            for (int s = 0; s < n; s += l + l)
                t = W[i] * A[s + i + l], A[s + i + l] = A[s + i] - t, A[s + i] += t;
    }
    if (inv == -1) for (int i = 0; i < n; i++) A[i] /= n;
}
template <typename T> vector<T> multiply(const vector<T> &A, const vector<T> &B, int p = 1e9 + 7) {
    assert(is_integral<T>::value);
    using CD = complex<double>; // or long double;
    using LL = long long;
    int s = A.size() + B.size() - 1;
    vector<CD> U, V;
    for (auto x : A) U.emplace_back(x >> 15, x & 32767);
    for (auto x : B) V.emplace_back(x >> 15, x & 32767);
    U.resize(s), V.resize(s), fourier(U, 1), fourier(V, 1);
    for (size_t i = 0, n = U.size(); i + i <= n; i++) {
        size_t j = (n - i) & (n - 1);
        auto a = U[i], b = U[j], c = V[i], d = V[j];
        U[i] = (a + conj(b)) * (c + conj(d)) * 0.25 - (a - conj(b)) * (c - conj(d)) * CD(0, 0.25);
        U[j] = (b + conj(a)) * (d + conj(c)) * 0.25 - (b - conj(a)) * (d - conj(c)) * CD(0, 0.25);
        V[i] = CD(0, 0.5) * (conj(b * d) - a * c), V[j] = CD(0, 0.5) * (conj(a * c) - b * d);
    }
    fourier(U, -1), fourier(V, -1);
    vector<T> R(s);
    for (int i = 0; i < s; i++) {
        LL t1 = (LL)(U[i].real() + 0.5) % p;
        LL t2 = (LL)(V[i].real() + 0.5) % p;
        LL t3 = (LL)(U[i].imag() + 0.5) % p;
        R[i] = ((t1 << 30) % p + (t2 << 15) % p + t3) % p;
    }
    return R;
}
};


// Luogu. 4245
int main() {
    int n, m, p;
    scanf("%d%d%d", &n, &m, &p);
    n++, m++;
    vector<int> P(n), Q(m);
    for (int i = 0; i < n; i++) scanf("%d", &P[i]);
    for (int i = 0; i < m; i++) scanf("%d", &Q[i]);
    auto R = MFFT::multiply(P, Q, p);
    for (size_t i = 0; i < R.size(); i++) printf("%d%c", R[i], " \n"[i + 1 == R.size()]);
    return 0;
}
```

## math/combine_big.cc

```c++
#include <bits/stdc++.h>
using namespace std;

// Lucas：when m is prime < 1e5，C(n,k)%m = C(n/m,k/m)*C(n%m,k%m)%m

namespace Combine {
using LL = long long;
int inv(LL x, int m) { return x > m ? inv(x % m, m) : x > 1 ? inv(m % x, m) * (m - m / x) % m : x; }
int comod(LL n, LL k, int m = 1e9 + 7) {
    if (k > n) return 0;
    if (k + k > n) return comod(n, n - k, m);
    int num = 1, den = 1;
    for (int i = 1; i <= k; i++) num = num * ((n - i + 1) % m) % m, den = 1LL * den * i % m;
    return 1LL * num * inv(den, m) % m;
}
int lucas(LL n, LL k, int m = 10007) {
    assert(m < 1e5);
    return n || k ? 1LL * lucas(n / m, k / m, m) * comod(n % m, k % m, m) % m : 1;
}
};


// 51Nod. 1269
int main() {
    using LL = long long;
    const int Mod = 1e9 + 7;
    int n;
    scanf("%d", &n);
    LL k, ans = 0;
    scanf("%lld", &k);
    vector<LL> S(n);
    for (int i = 0; i < n; i++) scanf("%lld", &S[i]);
    for (int s = 0; s < (1 << n); s++) {
        bool flag = __builtin_popcount(s) & 1;
        LL t = k;
        for (int i = 0; i < n; i++) if (1 << i & s) t -= S[i] + 1;
        if (t < 0) continue;
        ans += (flag ? -1 : 1) * Combine::comod(t + n - 1, n - 1, Mod);
        ans = (ans + Mod) % Mod;
    }
    printf("%lld\n", ans);
    return 0;
}
```

## math/number_divide.cc

```c++
#include <bits/stdc++.h>
#define FI(i,a,b) for(int i=(a);i<=(b);++i)
using namespace std;


// 51Nod. 1259
// Calc number of ways to divide a number
// for example, 4 => {4}, {1, 3}, {2, 2}, {1, 1, 2}, {1, 1, 1, 1}
const int Mod = 1e9 + 7;
int T[2005], bias = 1000; // Pentagonal number
int F[50005];

int main() {
    int n;
    cin >> n;
    FI(i, -bias, bias) T[i + bias] = i * (3 * i - 1) / 2;
    F[0] = 1;
    FI(i, 1, n) {
        FI(j, 1, i) {
            int x = T[j + bias];
            if (x > i) break;
            F[i] += (j & 1 ? 1 : -1) * F[i - x];
            F[i] = (F[i] % Mod + Mod) % Mod;
            x = T[bias - j];
            if (x > i) break;
            F[i] += (j & 1 ? 1 : -1) * F[i - x];
            F[i] = (F[i] % Mod + Mod) % Mod;
        }
    }
    printf("%d\n", F[n]);
    return 0;
}
```

## math/kth_fib.cc

```c++
#include <bits/stdc++.h>
using namespace std;

/* Fibonacci
 * F[1]+F[3]+...+F[2n-1] = F[2n]-F[2]+F[1]
 * F[2]+F[4]+...+F[2n] = F[2n+1]-F[1]
 * F[1]^2+F[2]^2+...+F[n]^2 = F[n]F[n+1]
 * F[2n] = F[n](F[n-1]+F[n+1])
 * F[2n-1] = F[n]^2 + F[n-1]^2
*/

// F[0] = 0, F[1] = 1, return {F[k], F[k-1]}
constexpr pair<int, int> kth_fib(long long k, int m = 1e9 + 7) {
    if (k <= 1) return make_pair(k, 0);
    auto t = kth_fib(k / 2, m);
    int x = t.first, y = t.second;
    int p = (1LL * x * x + 1LL * y * y) % m, q = x * (x + 2LL * y) % m;
    return k & 1 ? make_pair(int((0LL + p + q) % m), q) : make_pair(q, p);
}


int main() {
    auto p = kth_fib(1);
    printf("%d, %d\n", p.first, p.second);
    return 0;
}
```

## math/phi_func.cc

```c++
#include <bits/stdc++.h>
using namespace std;

// a ^ phi(m) % m = 1, euler's theorem
// a ^ (m-1) % m = 1, if gcd(a, m) = 1, fermat's little theorem
// a ^ n % m = a ^ (n % phi(m)) % m, if gcd(a, m) = 1
// a ^ n % m = a ^ (phi(m) + n % phi(m)) % m, if n >= log2(m) [or n >= phi(m)]
constexpr long long phi(long long n) {
    auto ret = n;
    for (auto i = 2LL; i * i <= n; i++)
        if (n % i == 0) { while (n % i == 0) n /= i; ret -= ret / i; }
    return n > 1 ? ret - ret / n : ret;
}



// CF. 906D
using LL = long long;
auto Mod = [](LL x, LL m) { return x < m ? x : x % m + m; };
LL powmod(LL a, LL k, LL m) { LL res = 1; for (a = Mod(a, m); k; k >>= 1, a = Mod(a * a, m)) if (k & 1)res = Mod(res * a, m); return res; }
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> A(n + 1);
    for (int i = 1; i <= n; i++) scanf("%d", &A[i]);
    int q;
    scanf("%d", &q);
    auto getPhi = [&](int n) {
        static unordered_map<int, int> M;
        if (M.count(n)) return M[n];
        return M[n] = phi(n);
    };
    function<int(int, int, int)> calc = [&](int l, int r, int m) {
        if (l == r || m == 1) return (int)Mod(A[l], m);
        return (int)powmod(A[l], calc(l + 1, r, getPhi(m)), m);
    };
    while (q--) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", calc(l, r, m) % m);
    }
    return 0;
}
```

## math/combine_small.cc

```c++
#include <bits/stdc++.h>
using namespace std;

struct CombineSmall {
    int m;
    vector<vector<int>> F;
    CombineSmall(int n, int m) : m(m), F(n) { for (int i = 1; i < n; i++) F[i].resize(i + 1); }
    int com(int n, int k) {
        return k > n ? 0 : k + k > n ? com(n, n - k) :
               F.at(n)[k] ? F[n][k] : F[n][k] = (com(n - 1, k) + com(n - 1, k - 1)) % m;
    }
};

int main() {
    return 0;
}
```

## math/euler_sieve.cc

```c++
#include <bits/stdc++.h>
using namespace std;


struct Sieve {
    vector<int> L, Phi, P;
    Sieve(int n): L(n), Phi(n, 1) {
        L[1] = 1;
        for (int x = 2; x < n; x++) {
            if (!L[x]) P.push_back(L[x] = x), Phi[x] = x - 1;
            for (auto p : P) {
                if (x * p >= n) break;
                L[x * p] = p;
                Phi[x * p] = Phi[x] * (p - (x % p != 0));
                if (x % p == 0) break;
            }
        }
    }

    vector<int> factorize(long long n) {
        vector<int> R;
        for (int i = 0; 1LL * P[i] * P[i] <= n; i++) {
            if (n % P[i]) continue;
            do { n /= P[i], R.push_back(P[i]); }
            while (n % P[i] == 0);
        }
        if (n > 1) R.push_back(n);
        return R;
    }
    vector<int> factorize_low(int n) {
        assert(n < (int)L.size());
        vector<int> R;
        while (n != 1) R.push_back(L[n]), n /= L[n];
        return R;
    }
};


// 51Nod. 1188
int main() {
    using LL = long long;
    const int N = 5000000;
    auto sv = new Sieve(N + 1);
    vector<LL> Ans(N + 1);
    for (int i = 1; i <= N; i++)
        for (int j = 2; i * j <= N; j++)
            Ans[i * j] += i * sv->Phi[j];
    for (int i = 1; i <= N; i++) Ans[i] += Ans[i - 1];
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        printf("%lld\n", Ans[n]);
    }
    return 0;
}
```

## math/ntt.cc

```c++
#include <bits/stdc++.h>
using namespace std;


namespace NTT {
// must exists n*k+1 = P, (1004535809, 3), (786433, 10)
static const int P = 998244353, G = 3;
template <typename T> void arrange(vector<T> &A) {
    int n = A.size();
    assert(n == (n & -n));
    for (int i = 1, x = 0, y = 0; i <= n; i++) {
        if (x > y) swap(A[x], A[y]);
        x ^= i & -i, y ^= n / (i & -i) >> 1;
    }
}
// int add(int x, int y) { return x + y < P ? x + y : x + y - P; }
int add(int x, int y) { return (x + y) % P; }
int mpow(long long a, int k) {  int r = 1; for (a %= P; k; k >>= 1, a = a * a % P) if (k & 1)r = r * a % P; return r; }
template <typename T> void fourier(vector<T> &A, int inv) {
    assert(inv == -1 || inv == 1);
    int n = 1 << (32 - __builtin_clz(A.size() - 1));
    A.resize(n), arrange(A);
    for (int l = 1; l < n; l <<= 1) {
        int wl = mpow(G, ((P - 1) / l >> 1) * (l + l + inv)), w = 1, t;
        for (int i = 0; i < l; i++, w = 1LL * w * wl % P)
            for (int s = 0; s < n; s += l + l)
                t = 1LL * w * A[s + i + l] % P, A[s + i + l] = add(A[s + i], P - t), A[s + i] = add(A[s + i], t);
    }
    int t = mpow(n, P - 2);
    if (inv == -1) for (int i = 0; i < n; i++) A[i] = 1LL * A[i] * t % P;
}
template <typename T> vector<T> multiply(vector<T> A, vector<T> B) {
    int s = A.size() + B.size() - 1;
    A.resize(s), B.resize(s), fourier(A, 1), fourier(B, 1);
    for (size_t i = 0; i < A.size(); i++) A[i] = 1LL * A[i] * B[i] % P;
    fourier(A, -1);
    A.resize(s);
    return A;
}
};


// 51Nod. 1028
int main() {
    char s[100005], t[100005];
    scanf("%s%s", s, t);
    int n = strlen(s), m = strlen(t);
    vector<int> A, B;
    for (int i = n - 1; i >= 0; i--) A.push_back(s[i] - '0');
    for (int i = m - 1; i >= 0; i--) B.push_back(t[i] - '0');
    auto R = NTT::multiply(A, B);
    for (size_t i = 0; i < R.size(); i++) {
        if (R[i] >= 10) {
            if (i + 1u == R.size()) R.push_back(0);
            R[i + 1] += R[i] / 10;
            R[i] %= 10;
        }
    }
    reverse(R.begin(), R.end());
    for (auto c : R) printf("%d", c);
    puts("");
    return 0;
}
```

## math/lagrange.cc

```c++
#include <bits/stdc++.h>
using namespace std;


struct Lagrange {
    using LL = long long;
    int n, m;
    vector<LL> Inv, Den;
    Lagrange(int n, int m): n(n), m(m), Inv(n, 1), Den(n, 1) {
        assert(n > 1);
        for (int i = 2; i < n; i++)
            Inv[i] = (m - m / i) * Inv[m % i] % m, Den[i] = Den[i - 1] * Inv[i] % m;
    }
    constexpr LL inv(LL x) { return x < 2 ? x : (m - m / x) * inv(m % x) % m; }
    constexpr LL sub(LL x, LL y) { return (x - y + m) % m; }
    constexpr LL add(LL x, LL y) { return (x + y) % m; }
    // O(k^2), naive
    template <typename T> LL interp(const vector<T> &X, const vector<T> &Y, LL x) {
        LL ans = 0;
        for (size_t i = 0; i < X.size(); i++) {
            LL num = Y.at(i), den = 1;
            for (size_t j = 0; j < X.size(); j++) if (j != i)
                    num = num * sub(x, X[j]) % m, den = den * sub(X[i], X[j]) % m;
            ans = (ans + num * inv(den)) % m;
        }
        return ans;
    }
    // O(k), for X is [0, 1, ..., k]
    template <typename T> LL interp_fast(const vector<T> &Y, LL x) {
        int k = (int)Y.size() - 1;
        assert(k < n);
        if (x <= k) return Y[x];
        vector<LL> Suf(1, 1);
        for (LL j = k, tmp = 1; j > 0; j--) Suf.push_back(tmp = tmp * sub(x, j) % m);
        LL ans = 0, den = Den[k];
        for (LL j = 0, pref = 1; j <= k; j++) {
            LL num = pref * Suf.back() % m;
            pref = pref * sub(x, j) % m, Suf.pop_back();
            LL t = num * den % m * Y[j] % m;
            ans = (k - j) & 1 ? sub(ans, t) : add(ans, t);
            if (j < k) den = den * Inv[j + 1] % m * (k - j) % m;
        }
        return ans;
    }
};



// CF. 995F
using LL = long long;
LL F[3005][3005];
int main() {
    LL n, D;
    cin >> n >> D;
    const int Mod = 1e9 + 7;
    vector<vector<int>> G(n + 1);
    for (int i = 2; i <= n; i++) {
        int x;
        scanf("%d", &x);
        G[x].push_back(i);
    }
    function<void(int)> dfs = [&](int u) {
        for (auto v : G[u]) {
            dfs(v);
        }
        for (int i = 1; i <= min(n, D); i++) {
            LL tmp = 1;
            for (auto v : G[u]) {
                tmp = tmp * F[v][i] % Mod;
            }
            F[u][i] = (F[u][i - 1] + tmp) % Mod;
        }
    };
    dfs(1);
    vector<LL> Y;
    for (int i = 0; i <= n; i++) Y.push_back(F[1][i]);
    Lagrange lg(n + 1, Mod);
    cout << lg.interp_fast(Y, D) << endl;
}
```

## math/prime_n.cc

```c++
#include <bits/stdc++.h>
using namespace std;


vector<int> prime_n(int n) {
    vector<int> Pr, L(n);
    L[1] = 1;
    for (int x = 2; x < n; x++) {
        if (!L[x]) Pr.push_back(L[x] = x);
        for (auto p : Pr) {
            if (x * p >= n) break;
            L[x * p] = p;
            if (x % p == 0) break;
        }
    }
    return Pr;
}


int main() {
    return 0;
}
```

## math/phi_n.cc

```c++
#include <bits/stdc++.h>
using namespace std;


vector<int> phi_n(int n) {
    vector<int> L(n), P, Phi(n);
    L[1] = 1;
    for (int x = 2; x < n; x++) {
        if (!L[x]) P.push_back(L[x] = x), Phi[x] = x - 1;
        for (auto p : P) {
            if (x * p >= n) break;
            L[x * p] = p;
            Phi[x * p] = Phi[x] * (p - (x % p != 0));
            if (x % p == 0) break;
        }
    }
    return Phi;
}


// 51Nod. 1188
int main() {
    using LL = long long;
    const int N = 5000000;
    auto Phi = phi_n(N + 1);
    vector<LL> Ans(N + 1);
    for (int i = 1; i <= N; i++)
        for (int j = 2; i * j <= N; j++)
            Ans[i * j] += i * Phi[j];
    for (int i = 1; i <= N; i++) Ans[i] += Ans[i - 1];
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        printf("%lld\n", Ans[n]);
    }
    return 0;
}
```

## math/mu_n.cc

```c++
#include <bits/stdc++.h>
using namespace std;


// Mu[1] = 1, if x = p1p2...pk, Mu[x] = (-1)^k, else 0
vector<int> mu_n(int n) {
    vector<int> Mu(n), L(n), P;
    Mu[1] = L[1] = 1;
    for (int x = 2; x < n; x++) {
        if (!L[x]) P.push_back(L[x] = x), Mu[x] = -1;
        for (auto p : P) {
            if (x * p >= n) break;
            L[x * p] = p;
            if (x % p == 0) { Mu[x * p] = 0; break; }
            else Mu[x * p] = -Mu[x];
        }
    }
    return Mu;
}


// 51Nod. 1180
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    if (n > m) swap(n, m);
    m--, n--;
    if (n == 0) return !printf(!m ? "0\n" : "1\n");
    auto Mu = mu_n(n + 1);
    auto tot = 0LL;
    for (int i = 1; i <= n; i++) {
        tot += 1LL * Mu[i] * (n / i) * (m / i);
    }
    cout << tot + 2 << endl;
    return 0;
}
```

## math/polynomial_inv.cc

```c++
#include <bits/stdc++.h>
using namespace std;


namespace MFFT {
static const double PI = acos(-1.0);
template <typename T> void arrange(vector<T> &A) {
    int n = A.size();
    assert(n == (n & -n));
    for (int i = 1, x = 0, y = 0; i <= n; i++) {
        if (x > y) swap(A[x], A[y]);
        x ^= i & -i, y ^= n / (i & -i) >> 1;
    }
}
template <typename T> void fourier(vector<complex<T>> &A, int inv) {
    assert((inv == 1 || inv == -1) && is_floating_point<T>::value);
    int n = 1 << (32 - __builtin_clz(A.size() - 1));
    A.resize(n), arrange(A);
    vector<complex<T>> W(n >> 1, {1, 0});
    for (int l = 1; l < n; l <<= 1) {
        complex<T> wl(cos(inv * PI / l), sin(inv * PI / l)), t;
        for (int i = l - 2; i >= 0; i -= 2) W[i] = W[i >> 1];
        for (int i = 1; i < l; i += 2) W[i] = W[i - 1] * wl;
        for (int i = 0; i < l; i++)
            for (int s = 0; s < n; s += l + l)
                t = W[i] * A[s + i + l], A[s + i + l] = A[s + i] - t, A[s + i] += t;
    }
    if (inv == -1) for (int i = 0; i < n; i++) A[i] /= n;
}
template <typename T> vector<T> multiply(const vector<T> &A, const vector<T> &B, int p = 1e9 + 7) {
    assert(is_integral<T>::value);
    using CD = complex<double>; // or long double;
    using LL = long long;
    int s = A.size() + B.size() - 1;
    vector<CD> U, V;
    for (auto x : A) U.emplace_back(x >> 15, x & 32767);
    for (auto x : B) V.emplace_back(x >> 15, x & 32767);
    U.resize(s), V.resize(s), fourier(U, 1), fourier(V, 1);
    for (size_t i = 0, n = U.size(); i + i <= n; i++) {
        size_t j = (n - i) & (n - 1);
        auto a = U[i], b = U[j], c = V[i], d = V[j];
        U[i] = (a + conj(b)) * (c + conj(d)) * 0.25 - (a - conj(b)) * (c - conj(d)) * CD(0, 0.25);
        U[j] = (b + conj(a)) * (d + conj(c)) * 0.25 - (b - conj(a)) * (d - conj(c)) * CD(0, 0.25);
        V[i] = CD(0, 0.5) * (conj(b * d) - a * c), V[j] = CD(0, 0.5) * (conj(a * c) - b * d);
    }
    fourier(U, -1), fourier(V, -1);
    vector<T> R(s);
    for (int i = 0; i < s; i++) {
        LL t1 = (LL)(U[i].real() + 0.5) % p;
        LL t2 = (LL)(V[i].real() + 0.5) % p;
        LL t3 = (LL)(U[i].imag() + 0.5) % p;
        R[i] = ((t1 << 30) % p + (t2 << 15) % p + t3) % p;
    }
    return R;
}
int mpow(long long a, int k, int m) { int r(1); for (a %= m; k; k >>= 1, a = a * a % m) if (k & 1)r = r * a % m; return r; }
template <typename T> vector<T> inv(const vector<T> &A, int n, int p) {
    assert(is_integral<T>::value && A[0]);
    vector<T> R;
    function<void(int)> inv_ = [&](int n) {
        if (n == 1) return R = {mpow(A[0], p - 2, p)}, void();
        inv_((n + 1) >> 1);
        auto Tmp = multiply(A, R, p);
        Tmp[0] = (2 - Tmp[0] + p) % p;
        for (size_t i = 1; i < Tmp.size(); i++) Tmp[i] = Tmp[i] ? p - Tmp[i] : 0;
        R = multiply(R, Tmp, p);
        R.resize(n);
    };
    inv_(n);
    return R;
}
};


// 51Nod. 1228
using LL = long long;
LL inv(LL x, LL m) { return x > m ? inv(x % m, m) : x > 1 ? inv(m % x, m) * (m - m / x) % m : x; }
LL mpow(LL a, LL k, LL m) { LL r(1); for (a %= m; k; k >>= 1, a = a * a % m) if (k & 1)r = r * a % m; return r; }

vector<int> bernouli_n(int n, int m = 1e9 + 7) {
    vector<int> A;
    for (int i = 0, tmp = 1; i < n; i++) {
        tmp = 1LL * tmp * (i + 1) % m;
        A.push_back(inv(tmp, m));
    }
    auto B = MFFT::inv(A, n, m);
    for (int i = 1, tmp = 1; i < n; i++) {
        tmp = 1LL * tmp * i % m;
        B[i] = 1LL * B[i] * tmp % m;
    }
    B[1] = inv(2, m);
    return B;
}

auto B = bernouli_n(50001);
int main() {
    using LL = long long;
    const int Mod = 1e9 + 7;
    vector<int> Inv(50002, 1);
    for (int i = 2; i <= 50001; i++) Inv[i] = 1LL * (Mod - Mod / i) * Inv[Mod % i] % Mod;
    int t;
    scanf("%d", &t);
    while (t--) {
        LL n, k;
        scanf("%lld%lld", &n, &k);
        LL ans = 0, tmp1 = mpow(n, k + 1, Mod), tmp2 = 1, invn = inv(n, Mod);
        for (int i = 0; i <= k; i++) {
            ans += B[i] * tmp1 % Mod * tmp2 % Mod;
            tmp1 = tmp1 * invn % Mod;
            tmp2 = tmp2 * (k + 1 - i) % Mod * Inv[i + 1] % Mod;
            ans %= Mod;
        }
        ans = ans * inv(k + 1, Mod) % Mod;
        printf("%lld\n", ans);
    }
    return 0;
}
```

## math/s_func.cc

```c++
#include <bits/stdc++.h>
using namespace std;


// Sum of divisors, partial multiplicative function
constexpr long long s_func(long long n) {
    auto ret = 1LL;
    for (auto i = 2LL; i * i <= n; i++) {
        if (n % i == 0) {
            auto sum = 1LL, cur = 1LL;
            while (n % i == 0) n /= i, cur *= i, sum += cur;
            ret *= sum;
        }
    }
    return n > 1 ? ret * (n + 1) : ret;
}


// Spoj. DIVSUM
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        printf("%d\n", int(s_func(n) - n));
    }
    return 0;
}
```

## math/newton_sqrt_root.cc

```c++
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

int main() {
    cout << sqrt_newton(3.6) << endl;
}
```

## math/exgcd.cc

```c++
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
```

## math/young_tableaus.cc

```c++
#include <bits/stdc++.h>
using namespace std;


// if A[i][j] has value, A[i+1][j] and A[i][j+1]
// must be null or greater than A[i][j]
// F[1] = 1, F[2] = 2, F[n] = F[n-1] + (n-1) * F[n-2]
// hook formula: given shape, F[n] = n! / product of all hook length,
// hook length = itself + right and down cells



// 51Nod. 1129
#define DEBUG(x) cerr << #x << ": " << (x) << endl;
using LL = long long ;
LL mpow(LL a, LL k, LL m) { LL r(1); for (a %= m; k; k >>= 1, a = a * a % m) if (k & 1)r = r * a % m; return r; }
vector<int> inv_n(int n, int m = int(1e9 + 7)) {
    vector<int> Inv(n);
    Inv[1] = 1;
    for (int x = 2; x < n; x++) Inv[x] = Inv[m % x] * 1LL * (m - m / x) % m;
    return Inv;
}
const int Mod = 10007;
const auto Inv = inv_n(Mod, Mod);
pair<int, int> factorial(int n) {
    static vector<int> Cycle;
    if (Cycle.empty()) {
        Cycle.resize(Mod);
        Cycle[0] = 1;
        for (int i = 1; i < Mod; i++) Cycle[i] = Cycle[i - 1] * i % Mod;
    }
    int q = n / Mod;
    int x = mpow(Cycle.back(), q, Mod) * Cycle[n % Mod] % Mod, y = q;
    if (q) {
        auto p = factorial(q);
        x = x * p.first % Mod;
        y += p.second;
    }
    return {x, y};
}

int calc(int n, int m) {
    assert(n <= m);
    auto num = factorial(n * m);
    auto den = 1LL, mod0 = 0LL;
    mod0 += num.second;
    for (int i = 1; i < n; i++) {
        if (i % Mod == 0) {
            mod0 -= i;
            den = den * mpow(i / Mod, i, Mod) % Mod;
        } else den = den * mpow(i, i, Mod) % Mod;
        int j = n + m - i;
        if (j % Mod == 0) {
            mod0 -= i;
            den = den * mpow(j / Mod, i, Mod) % Mod;
        } else den = den * mpow(j, i, Mod) % Mod;
    }
    auto p1 = factorial(m), p2 = factorial(n - 1);
    int x = p1.first * Inv[p2.first] % Mod, y = p1.second - p2.second;
    den = den * mpow(x, n, Mod) % Mod;
    mod0 -= y * n;
    if (mod0 != 0) return 0;
    return num.first * Inv[den] % Mod;
}

int main() {
    int N;
    scanf("%d", &N);
    int ans = 0;
    for (int n = 1; n * n <= N; n++) {
        if (N % n) continue;
        int m = N / n, tmp = calc(n, m);
        ans += tmp;
        if (m != n) ans += tmp;
        ans %= Mod;
    }
    printf("%d\n", ans);
    return 0;
}
```

## math/fft.cc

```c++
#include <bits/stdc++.h>
using namespace std;


namespace FFT {
static const double PI = acos(-1.0);
template <typename T> void arrange(vector<T> &A) {
    int n = A.size();
    assert(n == (n & -n));
    for (int i = 1, x = 0, y = 0; i <= n; i++) {
        if (x > y) swap(A[x], A[y]);
        x ^= i & -i, y ^= n / (i & -i) >> 1;
    }
}
template <typename T> void fourier(vector<complex<T>> &A, int inv) {
    assert((inv == 1 || inv == -1) && is_floating_point<T>::value);
    int n = 1 << (32 - __builtin_clz(A.size() - 1));
    A.resize(n), arrange(A);
    vector<complex<T>> W(n >> 1, {1, 0});
    for (int l = 1; l < n; l <<= 1) {
        complex<T> wl(cos(inv * PI / l), sin(inv * PI / l)), t;
        for (int i = l - 2; i >= 0; i -= 2) W[i] = W[i >> 1];
        for (int i = 1; i < l; i += 2) W[i] = W[i - 1] * wl;
        for (int i = 0; i < l; i++)
            for (int s = 0; s < n; s += l + l)
                t = W[i] * A[s + i + l], A[s + i + l] = A[s + i] - t, A[s + i] += t;
    }
    if (inv == -1) for (int i = 0; i < n; i++) A[i] /= n;
}
template <typename T> vector<T> multiply(const vector<T> &A, const vector<T> &B) {
    double bias = is_integral<T>::value ? 0.5 : 0;
    int s = A.size() + B.size() - 1;
    vector<complex<double>> U, V; // or long double
    for (auto x : A) U.emplace_back(x, 0);
    for (auto x : B) V.emplace_back(x, 0);
    U.resize(s), V.resize(s), fourier(U, 1), fourier(V, 1);
    for (size_t i = 0; i < U.size(); i++) U[i] *= V[i];
    fourier(U, -1);
    vector<T> R;
    for (int i = 0; i < s; i++) R.push_back(U[i].real() + bias);
    return R;
}
};


// 51Nod. 1028
int main() {
    char s[100005], t[100005];
    scanf("%s%s", s, t);
    int n = strlen(s), m = strlen(t);
    vector<int> A, B;
    for (int i = n - 1; i >= 0; i--) A.push_back(s[i] - '0');
    for (int i = m - 1; i >= 0; i--) B.push_back(t[i] - '0');
    auto R = FFT::multiply(A, B);
    for (size_t i = 0; i < R.size(); i++) {
        if (R[i] >= 10) {
            if (i + 1u == R.size()) R.push_back(0);
            R[i + 1] += R[i] / 10;
            R[i] %= 10;
        }
    }
    reverse(R.begin(), R.end());
    for (auto c : R) printf("%d", c);
    puts("");
    return 0;
}
```

## math/combine_log.cc

```c++
#include <bits/stdc++.h>
using namespace std;

/*
 * C(n, k) = C(n-1, k) + C(n-1, k-1), C(n, k) = C(n, k-1) * (n-k+1) / k
 * C(n, 0) + C(n, 1) + ... + C(n, n) = 2^n
 * C(n, 1) + ... = C(n, 0) + ... = 2^(n-1)
 * C(n, 0)^2 + ... + C(n, n)^2 = C(2*n, n)
*/

struct Combine {
    using LL = long long;
    int m;
    vector<LL> F;
    Combine(int n, int m) : m(m), F(n, 1) { for (int i = 1; i < n; i++) F[i] = F[i - 1] * i % m; }
    int inv(LL x) { return x > m ? inv(x % m) : x > 1 ? inv(m % x) * (m - m / x) % m : x; }
    int com(LL n, LL k) { return F.at(n) * inv(F.at(n - k) * F[k]) % m; }
    int per(LL n, LL k) { return F.at(n) * inv(F.at(k)) % m; }
};


int main() {
}
```

## flows/max_flow.cc

```c++
#include <bits/stdc++.h>
using namespace std;


template <typename T> struct MaxFlow {
    struct Edge { int u, v; T c, f; };
    const T eps = (T)1e-9;
    vector<Edge> E;
    int n, src, sink;
    vector<vector<int>> G;
    vector<int> P, D;
    T flow = T();
    MaxFlow(int n, int src, int sink): n(n), src(src), sink(sink), G(n), P(n), D(n) {}

    void clear_flow() { for (auto& e : E) e.f = T(); flow = T(); }
    void reduce() { for (auto& e : E) e.c -= e.f; }
    void add_edge(int u, int v, T cap) {
        assert(0 <= u && u < n && 0 <= v && v < n);
        G[u].push_back(E.size()), E.push_back({u, v, cap, T()});
        G[v].push_back(E.size()), E.push_back({v, u, T(), T()});
    }
    bool expath() {
        fill(D.begin(), D.end(), -1);
        queue<int> Q;
        Q.push(sink), D[sink] = 0;
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for (int id : G[u]) {
                const Edge& e = E[id], &b = E[id ^ 1];
                if (b.c - b.f > eps && D[e.v] == -1) {
                    D[e.v] = D[e.u] + 1, Q.push(e.v);
                    if (e.v == src) return true;
                }
            }
        }
        return false;
    }
    T dfs(int u, T w) {
        if (u == sink) return w;
        for (int& i = P[u]; i < int(G[u].size()); i++) {
            int id = G[u][i];
            const Edge& e = E[id];
            if (e.c - e.f > eps && D[e.v] == D[e.u] - 1) {
                T t = dfs(e.v, min(e.c - e.f, w));
                if (t > eps) return E[id].f += t, E[id ^ 1].f -= t, t;
            }
        }
        return T();
    }
    const T max_flow() {
        while (expath()) {
            fill(P.begin(), P.end(), 0);
            T tot = T();
            for (;;) {
                T add = dfs(src, numeric_limits<T>::max());
                if (add <= eps) break;
                tot += add;
            }
            if (tot <= eps) break;
            flow += tot;
        }
        return flow;
    }
    vector<int> min_cut() {
        max_flow();
        vector<int> R(n);
        for (int i = 0; i < n; i++) R[i] = (D[i] != -1);
        return R;
    }
};



// 51Nod. 1757
vector<int> Dis[2001];
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<vector<int>> G(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v), G[v].push_back(u);
    }
    vector<int> I(m + 1);
    for (int i = 1; i <= m; i++) {
        int id;
        scanf("%d", &id);
        I[i] = id;
        Dis[id].resize(n + 1);
        function<void(int, int, int)> dfs = [&](int u, int p, int dep) {
            Dis[id][u] = dep;
            for (auto v : G[u]) if (v != p) dfs(v, u, dep + 1);
        };
        dfs(id, -1, 0);
    }
    auto can = [&](int t) {
        int N = 2 + n + (t + 1) * m, src = 0, sink = N - 1;
        MaxFlow<int> mf(N, src, sink);
        for (int i = 1; i <= n; i++) mf.add_edge(src, i, 1);
        for (int i = 1; i <= m; i++) for (int j = 0; j <= t; j++) {
                int tmp = n + (i - 1) * (t + 1) + j + 1;
                mf.add_edge(tmp, sink, 1);
                if (j) mf.add_edge(tmp - 1, tmp, n);
            }
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++)
                if (Dis[I[j]][i] <= t) mf.add_edge(i, n + (j - 1) * (t + 1) + Dis[I[j]][i] + 1, 1);
        return mf.max_flow() == n;
    };
    int l = m - 1, r = n;
    while (l + 1 < r) {
        int m = (l + r + 1) / 2;
        if (can(m)) r = m;
        else l = m;
    }
    printf("%d\n", r);
    return 0;
}
```

## flows/min_cost_flow.cc

```c++
#include <bits/stdc++.h>
using namespace std;


template <typename T> struct MinCostFlow {
    struct Edge { int u, v; T c, w, f; };
    const T eps = T(1e-9), INF = numeric_limits<T>::max();
    vector<Edge> E;
    int n, src, sink;
    vector<vector<int>> G;
    T flow = T(), cost = T();
    MinCostFlow(int n, int src, int sink): n(n), src(src), sink(sink), G(n) {}

    void clear_flow() { for (auto& e : E) e.f = T(); flow = cost = T(); }
    void reduce() { for (auto& e : E) e.c -= e.f; }
    void add_edge(int u, int v, T cap, T cost) {
        assert(0 <= u && u < n && 0 <= v && v < n);
        G[u].push_back(E.size()), E.push_back({u, v, cap, cost, T()});
        G[v].push_back(E.size()), E.push_back({v, u, 0, -cost, T()});
    }
    T min_cost_flow(T f = -1) {
        if (f < 0) f = INF;
        if (flow > f) clear_flow();
        f -= flow;
        while (f > eps) {
            vector<T> D(n, INF);
            vector<int> Inq(n), P(n);
            queue<int> Q;
            Q.push(src), D[src] = T(), Inq[src] = 1;
            while (!Q.empty()) {
                int u = Q.front();
                Q.pop(), Inq[u] = 0;
                for (auto i : G[u]) {
                    const auto& e = E[i];
                    if (e.c - e.f > eps && D[e.v] > D[u] + e.w) {
                        D[e.v] = D[u] + e.w, P[e.v] = i;
                        if (!Inq[e.v]) Q.push(e.v), Inq[e.v] = 1;
                    }
                }
            }
            if (D[sink] == INF) break;
            T can = f;
            for (int u = sink; u != src; u = E[P[u]].u)
                can = min(can, E[P[u]].c - E[P[u]].f);
            f -= can, flow += can, cost += D[sink] * can;
            for (int u = sink; u != src; u = E[P[u]].u)
                E[P[u]].f += can, E[P[u] ^ 1].f -= can;
        }
        return cost;
    }
};


// 51Nod. 1392
int main() {
    int n;
    scanf("%d", &n);
    vector<array<int, 2>> A(n + 1);
    for (int i = 1; i <= n; i++) scanf("%d%d", &A[i][0], &A[i][1]);
    sort(A.begin() + 1, A.end());
    A.erase(unique(A.begin() + 1, A.end()), A.end());
    n = A.size() - 1;
    int src = 0, sink = 2 * n + 1;
    MinCostFlow<double> G(n * 2 + 2, src, sink);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += A[i][0] * A[i][1];
        G.add_edge(src, i, 1, 0);
        G.add_edge(i + n, sink, 1, 0);
        for (int j = 1; j <= n; j++) {
            if (i == j || A[j][0] < A[i][0] || A[j][1] < A[i][1]) continue;
            G.add_edge(i, j + n, 1, -A[i][0] * A[i][1]);
        }
    }
    printf("%d\n", ans + (int)G.min_cost_flow());
    return 0;
}
```

## graphs/scc.cc

```c++
#include <bits/stdc++.h>
using namespace std;


// return color array
vector<int> tarjan_scc(const vector<vector<int>> &G) {
    int n = int(G.size()), ts = 0, nc = 0, t = 0;
    vector<int> C(n, -1), In(n), L(n), S(n + 1, -1);
    auto dfs = [&](int u, auto f) -> void {
        In[u] = L[u] = ++ts, S[t++] = u;
        for (auto v : G[u]) {
            if (!In[v]) f(v, f), L[u] = min(L[u], L[v]);
            else if (C[v] < 0) L[u] = min(L[u], In[v]);
        }
        if (L[u] == In[u]) { while (t && S[t] != u) C[S[--t]] = nc; nc++; }
    };
    for (size_t i = 0; i < G.size(); i++) if (!In[i]) dfs(i, dfs);
    return C;
}


int main() {
    return 0;
}
```

## graphs/bcc_edge.cc

```c++
#include <bits/stdc++.h>
using namespace std;


// return Low array as color array
// reverse edge should be update by min(Low[u], In[v]),
// but for edge bcc, it seems ok to use min(Low[u], Low[v])
vector<int> bcc_edge(const vector<vector<int>> &G) {
    int n = int(G.size()), ts = 0, t = 0;
    vector<int> In(n), L(n), S(n + 1);
    auto dfs = [&](int u, int p, auto f) -> void {
        L[u] = In[u] = ++ts, S[t++] = u;
        for (auto v : G[u]) if (v != p) { if (!In[v]) f(v, u, f); L[u] = min(L[u], L[v]); }
        if (In[u] == L[u]) while (t && S[t] != u) L[S[--t]] = L[u];
    };
    for (int i = 0; i < n; i++) if (!In[i]) dfs(i, -1, dfs);
    return L;
}


int main() {
    return 0;
}
```

## graphs/topo_sort.cc

```c++
#include <bits/stdc++.h>
using namespace std;


vector<int> tpsort(const vector<vector<int>> &G, bool dir = true) {
    vector<int> R, D(G.size());
    for (const auto &V : G) for (auto x : V) D[x]++;
    for (size_t i = 0; i < G.size(); i++) if (D[i] == !dir) R.push_back(i);
    for (size_t i = 0; i < R.size(); i++)
        for (auto x : G[R[i]]) if (--D[x] == !dir) R.push_back(x);
    return R;
}


int main() {
}
```

## graphs/dominator_tree.cc

```c++
#include <bits/stdc++.h>
using namespace std;


vector<vector<int>> get_dominator_tree(const vector<vector<int>> &G, int root) {
    int n = (int)G.size(), sz = 0;
    vector<int> In(n, -1), A(n), Idom(n), Semi(n), B(n), Fa(n), Pa(n);
    vector<vector<int>> Dom(n), rG(n), Ret(n);
    for (int u = 0; u < n; Fa[u] = B[u] = Semi[u] = u, u++)
        for (auto v : G[u]) rG[v].push_back(u);
    auto dfs = [&](int u, auto f) -> void {
        In[u] = sz, A[sz++] = u;
        for (auto v : G[u]) if (!~In[v]) f(v, f), Pa[In[v]] = In[u];
    };
    dfs(root, dfs);
    auto get = [&](int x, auto f) -> int {
        if (x == Fa[x]) return x;
        int y = f(Fa[x], f);
        if (Semi[B[Fa[x]]] < Semi[B[x]]) B[x] = B[Fa[x]];
        return Fa[x] = y;
    };
    for (int i = sz - 1, u, v; u = A[i], i > 0; --i) {
        for (auto rv : rG[u]) if (~(v = In[rv]))
                get(v, get), Semi[i] = min(Semi[i], Semi[B[v]]);
        Dom[Semi[i]].push_back(i);
        int x = Fa[i] = Pa[i];
        for (auto z : Dom[x]) get(z, get), Idom[z] = Semi[B[z]] < x ? B[z] : x;
        Dom[x].clear();
    }
    for (int i = 1; i < sz; i++) {
        if (Semi[i] != Idom[i]) Idom[i] = Idom[Idom[i]];
        Dom[Idom[i]].push_back(i);
    }
    for (int u = 0; u < n; u++) for (auto v : Dom[u]) Ret[A[u]].push_back(A[v]);
    return Ret;
}


// Luogu. 5180
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<vector<int>> G(n + 1);
    while (m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
    }
    auto R = get_dominator_tree(G, 1);
    vector<int> F(n + 1);
    auto dfs = [&](int u, int p, auto f) -> void {
        F[u] = 1;
        for (auto v : R[u]) if (v != p)
                f(v, u, f), F[u] += F[v];
    };
    dfs(1, 0, dfs);
    for (int i = 1; i <= n; i++) printf("%d%c", F[i], " \n"[i == n]);
}
```

## graphs/maximum_clique.cc

```c++
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
```

## graphs/bcc_vertex.cc

```c++
#include <bits/stdc++.h>
using namespace std;

// {u, v} not split to {u, v} and {v, u}
template <class Edge> vector<int> bcc_vetex(const vector<Edge> &E, const vector<vector<int>> &G) {
    int n = int(G.size()), m = int(E.size()), ts = 0, t = 0, c = 0;
    vector<int> In(n), L(n), S(m), B(m), C(m);
    auto dfs = [&](int u, auto f) -> void {
        L[u] = In[u] = ++ts;
        for (auto i : G[u]) {
            int v = E[i].u == u ? E[i].v : E[i].u;
            if (!B[i]) S[++t] = i, B[i] = 1;
            if (!In[v]) {
                f(v, f), L[u] = min(L[u], L[v]);
                if (L[v] >= In[u]) { ++c; do C[S[t]] = c; while (S[t--] != i); }
            } else L[u] = min(L[u], In[v]);
        }
    };
    for (int i = 0; i < n; i++) if (!In[i]) dfs(i, dfs);
    return C;
}


// CF. 962F
const int N = 1e5 + 5;
int n, m, F[N], Cv[N], Ce[N];
struct Edge { int u, v; };
vector<Edge> E(1);
vector<vector<int>> G(N);
vector<int> S[N];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].emplace_back(i), G[v].emplace_back(i);
        E.push_back({u, v});
    }
    auto C = bcc_vetex(E, G);
    int mx = *max_element(C.begin(), C.end());
    for (int i = 1; i <= m; i++) {
        Ce[C[i]]++;
        S[C[i]].push_back(E[i].u);
        S[C[i]].push_back(E[i].v);
    }
    for (int i = 1; i <= mx; i++) {
        sort(S[i].begin(), S[i].end());
        S[i].erase(unique(S[i].begin(), S[i].end()), S[i].end());
    }
    for (int i = 1; i <= m; i++)
        if (Ce[C[i]] == (int)S[C[i]].size()) F[i] = 1;
    printf("%d\n", accumulate(F, F + 1 + m, 0));
    for (int i = 1; i <= m; i++) if (F[i]) printf("%d ", i);
    puts("");
    return 0;
}
```

## dp/longest_arithmetic_series.cc

```c++
#include <bits/stdc++.h>
#define FI(i,a,b) for(int i=(a);i<=(b);++i)
#define FD(i,b,a) for(int i=(b);i>=(a);--i)
using namespace std;


// 51Nod. 1055
const int N = 10001;
short F[N][N + 1];
int main() {
    int n;
    scanf("%d", &n);
    vector<int> A(n + 1);
    FI(i, 1, n) scanf("%d", &A[i]);
    sort(A.begin() + 1, A.end());
    unordered_map<int, int> M;
    FI(i, 1, n) M[A[i]] = i;
    int ans = 2;
    for (int j = n; j >= 2; j--) {
        for (int i = j - 1; i >= 1; i--) {
            int d = A[j] - A[i];
            if (1LL * d * ans > A[n] - A[1]) break;
            int t = A[j] + d;
            if (!M.count(t)) F[i][j] = 2;
            else F[i][j] = F[j][M[t]] + 1;
            ans = max(ans, (int)F[i][j]);
        }
    }
    printf("%d\n", ans);
}
```

## dp/convex_hull_optimization.cc

```c++
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FI(i,a,b) for(int i=(a);i<=(b);++i)


// CF. 1083E
const int N = 1e6 + 5;
struct State { int x, y; LL a; };
int n, hq = 0, tq = 1, Q[N];
LL ans = 0, F[N];
State S[N];

double slope(int j, int i) { return 1. * (F[i] - F[j]) / (S[i].x - S[j].x); }
LL calc(int j, int i) { return F[j] + 1LL * S[i].y * (S[i].x - S[j].x) - S[i].a; }


int main() {
    scanf("%d", &n);
    FI(i, 1, n) scanf("%d%d%lld", &S[i].x, &S[i].y, &S[i].a);
    sort(S + 1, S + 1 + n, [&](const auto & a, const auto & b) { return a.x < b.x; });
    FI(i, 1, n) {
        while (hq + 1 < tq && calc(Q[hq], i) < calc(Q[hq + 1], i)) hq++;
        F[i] = calc(Q[hq], i);
        ans = max(ans, F[i]);
        while (hq + 1 < tq && slope(Q[tq - 2], Q[tq - 1]) < slope(Q[tq - 1], i)) tq--;
        Q[tq++] = i;
    }
    printf("%lld\n", ans);
}
```

## dp/single_cycle_tree.cc

```c++
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using PII = pair<int, int>;

// CF. 835F
const int N = 2e5 + 5;
int n, rt, Use[N], Dis[N], In[N], tp = 0, Path[N];
vector<PII> G[N];
LL Pre[N], Suf[N], Fir[N], Las[N], F[N], H[N];

int findcycle(int u, int p) {
    if (Use[u]) return rt = u, 1;
    Use[u] = 1;
    for (auto [v, w] : G[u]) if (v != p) {
            int ret = findcycle(v, u);
            if (ret == 1) {
                Dis[++tp] = w, Path[tp] = u, In[u] = 1;
                if (u != rt) return 1;
            }
            if (ret) return 2;
        }
    return 0;
}
void dp(int u, int p) {
    LL m1 = 0, m2 = 0, tmp;
    for (auto [v, w] : G[u]) if (v != p && !In[v]) {
            dp(v, u), tmp = F[v] + w;
            if (tmp > m1) m2 = m1, m1 = tmp;
            else if (tmp > m2) m2 = tmp;
            H[u] = max(H[v], H[u]);
        }
    F[u] = m1, H[u] = max(H[u], m1 + m2);
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int u, v, l;
        scanf("%d%d%d", &u, &v, &l);
        G[u].emplace_back(v, l);
        G[v].emplace_back(u, l);
    }
    findcycle(1, -1);
    LL mx = 0, len = 0;
    for (int i = 1, u; i <= tp; i++) {
        u = Path[i], dp(u, -1);
        Fir[i] = max(Fir[i - 1], len + F[u]);
        Pre[i] = max(Pre[i - 1], max(H[u], F[u] + mx));
        if (F[u] > mx) mx = F[u];
        mx += Dis[i + 1], len += Dis[i + 1];
    }
    mx = 0, len = 0;
    for (int i = tp, u; i >= 1; i--) {
        u = Path[i];
        Las[i] = max(Las[i + 1], len + F[u]);
        Suf[i] = max(Suf[i + 1], max(H[u], F[u] + mx));
        if (F[u] > mx) mx = F[u];
        mx += Dis[i], len += Dis[i];
    }
    LL ans = Pre[tp];
    for (int i = 1; i < tp; i++) {
        ans = min(ans, max({Pre[i], Suf[i + 1], Dis[1] + Fir[i] + Las[i + 1]}));
    }
    printf("%lld\n", ans);
    return 0;
}
```

## dp/quadrangle_optimization.cc

```c++
#include <bits/stdc++.h>
using namespace std;


// 51Nod. 1022
int F[2002][2002], S[2002][2002];
int main() {
    int n;
    scanf("%d", &n);
    vector<int> A(n + 1);
    for (int i = 1; i <= n; i++) scanf("%d", &A[i]);
    A.insert(A.end(), A.begin() + 1, A.end());
    for (int i = 1; i <= n * 2; i++) A[i] += A[i - 1];
    memset(F, 10, sizeof F);
    for (int i = 1; i <= n * 2; i++) S[i][i] = i, F[i][i] = 0;
    for (int len = 2; len <= n * 2; len++) {
        for (int i = 1; i + len - 1 <= n * 2; i++) {
            int j = i + len - 1;
            for (int k = S[i][j - 1]; k < j && k <= S[i + 1][j]; k++) {
                int tmp = F[i][k] + F[k + 1][j];
                if (tmp < F[i][j]) F[i][j] = tmp, S[i][j] = k;
            }
            F[i][j] += A[j] - A[i - 1];
        }
    }
    auto ans = INT_MAX;
    for (int i = 1; i <= n; i++) ans = min(ans, F[i][i + n - 1]);
    printf("%d\n", ans);
    return 0;
}
```

## ds/sparse_table.cc

```c++
#include <bits/stdc++.h>
using namespace std;


template <class T> struct STable {
    vector<vector<T>> F;
    function<T(T, T)> op;
    STable(const vector<T> &A, function<T(T, T)> op = [](T a, T b) { return min(a, b); }
          ): F(32 - __builtin_clz(A.size()), A), op(op)  {
        for (size_t c = 0; c + 1 < F.size(); c++) for (size_t i = 0; i < A.size(); i++)
                F[c + 1][i] = i + (1 << c) < A.size() ? op(F[c][i], F[c][i + (1 << c)]) : F[c][i];
    }
    T query(int l, int r) { int c = 31 - __builtin_clz(r - l); return op(F[c][l], F[c][r - (1 << c)]); }
};


int main() {
    STable<int> st(vector<int>(1000), [](int a, int b) { return max(a, b); });
}
```

## ds/dsu.cc

```c++
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> F;
    DSU(int n): F(n, -1) {}
    int root(int x) { return F[x] < 0 ? x : F[x] = root(F[x]); }
    int size(int x) { return -F[root(x)]; }
    bool same(int x, int y) { return root(x) == root(y); }
    bool unite(int x, int y) {
        x = root(x), y = root(y);
        if (x != y) { if (F[y] < F[x]) swap(x, y); F[x] += F[y], F[y] = x; }
        return x != y;
    }
};
```

## ds/persistent_array.cc

```c++
#include <bits/stdc++.h>
using namespace std;


template <typename T> struct PArray {
    const int n;
    vector<array<int, 2>> D;
    vector<int> R;
    vector<T> V;
    PArray(int n): n(n), D(n), R(1, 1), V(n, T()) {
        for (int i = n - 1; i; i--) D[i] = {i << 1, i << 1 | 1};
        for (auto &d : D) for (int i : {0, 1}) if (d[i] >= n) d[i] -= n;
    }

    int get_ver(int t) { return t < 0 ? t + (int)R.size() : t; }
    void new_ver(int t = -1) { D.emplace_back(D[R[get_ver(t)]]); R.push_back(D.size() - 1u); }
    void modify(int p, T x, int t = -1) {
        int h = 30 - __builtin_clz(p += n), no = D.size(), tmp = no, o, i;
        assert(n <= p && p < n + n), D.resize((int)D.size() + h + 2);
        for (o = R[get_ver(t)]; h; ++no, --h)
            i = !!(1 << h & p), D[no] = D[o], D[no][i] = no + 1, o = D[o][i];
        D[no] = D[o], D[no][p & 1] = V.size(), V.push_back(x), R[get_ver(t)] = tmp;
    }
    T query(int p, int t = -1) {
        int o = R[get_ver(t)];
        for (int h = 30 - __builtin_clz(p += n); h >= 0; h--) o = D[o][!!(1 << h & p)];
        return V[o];
    }
};


int main() {
    PArray<unsigned> p(10);
    p.modify(0, 100);
    cout << p.query(0) << endl;
    return 0;
}
```

## ds/treap.cc

```c++
#include <bits/stdc++.h>
using namespace std;


namespace Treap {
using T = int;
struct Node { T x; Node *l = 0, *r = 0; int p = rand(), c = 1; Node(T x) : x(x) {} };
using P = Node *;

int cnt(P t) { return !t ? 0 : t->c; }
void up(P t) { if (t) t->c = 1 + cnt(t->l) + cnt(t->r); }
bool has(P t, T x) { return !t ? 0 : x == t->x ? 1 : has(x < t->x ? t->l : t->r, x); }
int index(P t, T x) { return !t ? 0 : x <= t->x ? index(t->l, x) : cnt(t->l) + 1 + index(t->r, x); }
int rindex(P t, T x) { return !t ? 0 : x >= t->x ? rindex(t->r, x) : cnt(t->r) + 1 + rindex(t->l, x); }
T at(P t, int i) { int u = cnt(t->l); return i == u ? t->x : i < u ? at(t->l, i) : at(t->r, i - ++u); }
void split(P t, T x, P &l, P &r) {
    !t ? void(l = r = 0) : x < t->x ?
    (r = t, split(t->l, x, l, r->l), up(r)) : (l = t, split(t->r, x, l->r, r), up(l));
}
void merge(P &t, P l, P r) {
    !l || !r ? void(t = l ? l : r) : l->p > r->p ?
    (merge(l->r, l->r, r), up(t = l)) : (merge(r->l, l, r->l), up(t = r));
}
void insert(P &t, T x) { P u, v; split(t, x, u, v); merge(u, u, new Node(x)); merge(t, u, v); }
void erase(P &t, T x) { if (t) t->x == x ? merge(t, t->l, t->r) : erase(x < t->x ? t->l : t->r, x), up(t); }
};


// Luogu. 3369
int main() {
    using namespace Treap;
    int n;
    scanf("%d", &n);
    P tr = nullptr;
    while (n--) {
        int t, x;
        scanf("%d%d", &t, &x);
        if (t == 1) insert(tr, x);
        else if (t == 2) erase(tr, x);
        else if (t == 3) printf("%d\n", index(tr, x) + 1);
        else if (t == 4)  printf("%d\n", at(tr, x - 1));
        else if (t == 5) printf("%d\n", at(tr, index(tr, x) - 1));
        else printf("%d\n", at(tr, cnt(tr) - rindex(tr, x)));
    }
    return 0;
}
```

## ds/exact_cover.cc

```c++
#include <bits/stdc++.h>
using namespace std;


// r and c are 1-indexed
struct DLX {
    int n, m, sz;
    vector<int> S, R, U, L, D, I, J;
    DLX(int n, int m, vector<pair<int, int>> P) : n(n), m(m), sz(0), S(m + 1) {
        assert(n > 0 && m > 0);
        sort(P.begin(), P.end());
        add(1, 0, m, 0, 0, 0);
        for (int i = 1; i <= m; i++) add((i + 1) % (m + 1), i, i - 1, i, 0, i);
        sz = m + 1;
        vector<int> C(m + 1), F(n + 1);
        iota(C.begin(), C.end(), 0);
        for (auto p : P) {
            int r = p.first, c = p.second;
            assert(0 < r && r <= n && 0 < c && c <= m);
            if (!F[r]) add(sz, C[c], sz, c, r, c), F[r] = sz;
            else add(F[r], C[c], sz - 1, c, r, c);
            L[R[sz]] = R[L[sz]] = U[D[sz]] = D[U[sz]] =  sz, C[c] = sz++, S[c]++;
        }
    }
    void add(int r, int u, int l, int d, int i, int j) {
        R.push_back(r), U.push_back(u), L.push_back(l), \
        D.push_back(d), I.push_back(i), J.push_back(j);
    }
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
    vector<vector<int>> ans(int n_ans = 1, const vector<int> &Used = {}) {
        for (auto c : Used) assert(1 <= c && c <= m), remove(c);
        vector<vector<int>> Ans;
        vector<int> Tmp;
        function<void()> dfs = [&]() {
            if (n_ans < 1) return;
            if (!R[0]) { n_ans--; Ans.emplace_back(Tmp); return; }
            int c = R[0];
            for (int i = c; i; i = R[i]) if (S[i] < S[c]) c = i;
            remove(c);
            for (int i = D[c]; i != c; i = D[i]) {
                Tmp.push_back(I[i]);
                for (int j = R[i]; j != i; j = R[j]) remove(J[j]);
                dfs(), Tmp.pop_back();
                if (n_ans < 1) return;
                for (int j = L[i]; j != i; j = L[j]) restore(J[j]);
            }
            restore(c);
        };
        return dfs(), Ans;
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
```

## ds/matrix.cc

```c++
#include <bits/stdc++.h>
using namespace std;


// n x m matrix
template <typename T> struct Matrix {
    vector<vector<T>> D;
    using Func = function<T(T, T)>;
    Func add, mul;
    Matrix(size_t n, size_t m, Func add = plus<T>(), Func mul = multiplies<T>()
          ): D(n, vector<T>(m)), add(add), mul(mul) {}

    size_t n() const { return D.size(); }
    size_t m() const { return n() == 0 ? 0 : D[0].size(); }
    vector<T>& operator[](int i) { return D[i]; }
    const vector<T>& operator[](int i) const { return D[i]; }
    Matrix<T> operator *(const Matrix<T>& N) const {
        assert(m() == N.n());
        Matrix<T> R(n(), N.m(), add, mul);
        auto [im, jm, km, tmp] = tuple(n(), N.m(), m(), T());
        for (size_t i = 0; i < im; ++i)
            for (size_t j = 0; j < jm; ++j)
                for (size_t k = 0; k < km; ++k)
                    tmp = mul(D[i][k], N[k][j]), R[i][j] = k == 0 ? tmp : add(R[i][j], tmp);
        return R;
    }
    Matrix<T> pow(long long k) const {
        assert(k > 0 && m() == n());
        Matrix<T> R(n(), n(), add, mul);
        bool init = true;
        for (auto t = *this; k; t = t * t, k >>= 1)
            if (k & 1) R = init ? t : R * t, init = false;
        return R;
    }
};


// 51Nod. 1113
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    const int Mod = 1e9 + 7;
    Matrix<int> M(n + 1, n + 1,
    [](int x, int y) { return (x + y) % Mod; },
    [](int x, int y) -> int { return 1LL * x * y % Mod; });
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) scanf("%d", &M[i][j]);
    M = M.pow(m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) printf("%d%c", M[i][j], " \n"[j == n]);
    }
    return 0;
}
```

## ds/dsu_pst.cc

```c++
#include <bits/stdc++.h>
using namespace std;


struct PDSU {
    const int n;
    vector<array<int, 2>> D;
    vector<int> V, R;
    PDSU(int n): n(n), D(n), V(n, -1), R(1, 1) {
        for (int i = n - 1; i; i--) D[i] = {i << 1, i << 1 | 1};
        for (auto &d : D) for (int i : {0, 1}) if (d[i] >= n) d[i] -= n;
    }

    int get_ver(int t) { return t < 0 ? t + (int)R.size() : t; }
    void new_ver(int t = -1) { R.push_back(R[get_ver(t)]); }
    void modify(int p, int x, int t = -1) {
        int h = 30 - __builtin_clz(p += n), no = D.size(), tmp = no, o, i;
        assert(n <= p && p < n + n), D.resize((int)D.size() + h + 1);
        for (o = R[get_ver(t)]; h; ++no, --h)
            i = !!(1 << h & p), D[no] = D[o], D[no][i] = no + 1, o = D[o][i];
        D[no] = D[o], D[no][p & 1] = V.size(), V.push_back(x), R[get_ver(t)] = tmp;
    }
    int query(int p, int t = -1) {
        int o = R[get_ver(t)];
        for (int h = 30 - __builtin_clz(p += n); h >= 0; h--) o = D[o][!!(1 << h & p)];
        return V[o];
    }
    int root(int x, int t = -1) { int p = query(x, t); return p < 0 ? x : root(p, t); }
    bool same(int x, int y, int t = -1) { return root(x, t) == root(y, t); }
    int size(int x, int t = -1) { return -query(root(x, t), t); }
    bool unite(int x, int y, int t = -1) {
        x = root(x, t), y = root(y, t);
        if (x != y) {
            int sx = size(x, t), sy = size(y, t);
            if (sx < sy) swap(x, y);
            modify(x, -sx - sy, t), modify(y, x, t);
        }
        return x != y;
    }
};


// Luogu. 3402
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    PDSU uf(n + 1);
    for (int i = 1; i <= m; i++) {
        int t, a, b, k;
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d%d", &a, &b);
            uf.new_ver();
            uf.unite(a, b);
        } else if (t == 2) {
            scanf("%d", &k);
            uf.new_ver(k);
        } else {
            scanf("%d%d", &a, &b);
            uf.new_ver();
            puts(uf.same(a, b) ? "1" : "0");
        }
    }
    return 0;
}
```

## ds/dsu_rope.cc

```c++
#include <bits/stdc++.h>
#include <ext/rope>
using namespace std;
using namespace __gnu_cxx;


struct PDSU {
    vector<rope<int>> F;
    PDSU(int n): F(1, rope<int>(n, -1)) {}

    int get_ver(int t) { return t < 0 ? t + (int)F.size() : t; }
    void new_ver(int t = -1) { F.emplace_back(F[get_ver(t)]); }
    void modify(int p, int x, int t = -1) {
        if (t < 0) F.emplace_back(F.back());
        F[get_ver(t)].replace(p, x);
    }
    int query(int x, int t = -1) { return F[get_ver(t)].at(x); }
    int root(int x, int t = -1) { int p = query(x, t); return p < 0 ? x : root(p, t); }
    bool same(int x, int y, int t = -1) { return root(x, t) == root(y, t); }
    int size(int x, int t = -1) { return -query(x, t); }
    bool unite(int x, int y, int t = -1) {
        x = root(x, t), y = root(y, t);
        if (x != y) {
            int sx = size(x, t), sy = size(y, t);
            if (sx < sy) swap(x, y);
            modify(x, -sx - sy, t), modify(y, x, t);
        }
        return x != y;
    }
};


// Luogu. 3402
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    PDSU uf(n + 1);
    for (int i = 1; i <= m; i++) {
        int t, a, b, k;
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d%d", &a, &b);
            if (!uf.unite(a, b)) uf.new_ver();
        } else if (t == 2) {
            scanf("%d", &k);
            uf.new_ver(k);
        } else {
            scanf("%d%d", &a, &b);
            uf.new_ver();
            puts(uf.same(a, b) ? "1" : "0");
        }
    }
    return 0;
}
```

## ds/rope.cc

```c++
#include <bits/stdc++.h>
#include <ext/rope>
using namespace std;
using namespace __gnu_cxx;


// rope is used for insert, delete, access at O(n*sqrt(n))
int main() {
    rope<int> t;
    t.push_back(1);
    t.push_front(2);
    t.insert(1, 3);
    t.erase(2);
    t.replace(0, 5);
    t.substr(0, 2);
    t.at(2);
    t.clear();
}
```

## ds/implicit_treap.cc

```c++
#include <bits/stdc++.h>
using namespace std;


namespace ITreap {
using T = int;
struct Node { T x; Node *l = 0, *r = 0; int p = rand(), c = 1; bool b = 0; Node(T x) : x(x) {} };
using P = Node *;

int cnt(P t) { return !t ? 0 : t->c; }
void up(P t) { if (t) t->c = 1 + cnt(t->l) + cnt(t->r); }
void push(P t) { if (t && t->b) {t->b = 0, swap(t->l, t->r); if (t->l) t->l->b ^= 1; if (t->r) t->r->b ^= 1;}}
T at(P t, int i) { push(t); int u = cnt(t->l); return i == u ? t->x : i < u ? at(t->l, i) : at(t->r, i - ++u); }
void split(P t, P &l, P &r, int k, int a = 0) {
    !t ? void(l = r = 0) : (push(t), k <= a + cnt(t->l)) ?
    (r = t, split(t->l, l, r->l, k, a), up(r)) :
    (l = t, split(t->r, l->r, r, k, a + 1 + cnt(t->l)), up(l));
}
void merge(P &t, P l, P r) {
    push(l), push(r), !l || !r ? void(t = l ? l : r) : l->p > r->p ?
    (merge(l->r, l->r, r), up(t = l)) : (merge(r->l, l, r->l), up(t = r));
}
void insert(P &t, int i, T x) { P u, v; split(t, u, v, i); merge(u, u, new Node(x)); merge(t, u, v); }
void erase(P &t, int i) {
    if (t) cnt(t->l) == i ? merge(t, t->l, t->r) :
        cnt(t->l) > i ? erase(t->l, i) : erase(t->r, i - cnt(t->l) - 1), up(t);
}
void reverse(P &t, int l, int r) {
    P u, v, w;
    split(t, u, v, l), split(v, v, w, r - l);
    v->b ^= 1, merge(t, u, v), merge(t, t, w);
}
};


// Luogu. 3391
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    ITreap::P t = nullptr;
    for (int i = 1; i <= n; i++) ITreap::insert(t, i - 1, i);
    while (m--) {
        int l, r;
        scanf("%d%d", &l, &r);
        l--;
        ITreap::reverse(t, l, r);
    }
    for (int i = 0; i < n; i++)
        printf("%d%c", ITreap::at(t, i), " \n"[i + 1 == n]);
    return 0;
}
```

## ds/ptreap.cc

```c++
#include <bits/stdc++.h>
using namespace std;


namespace PTreap {
using T = int;
struct Node { T x; Node *l = 0, *r = 0; int p = rand(), c = 1; Node(T x) : x(x) {} };
using P = Node *;

int cnt(P t) { return !t ? 0 : t->c; }
void up(P t) { if (t) t->c = 1 + cnt(t->l) + cnt(t->r); }
bool has(P t, T x) { return !t ? 0 : x == t->x ? 1 : has(x < t->x ? t->l : t->r, x); }
int index(P t, T x) { return !t ? 0 : x <= t->x ? index(t->l, x) : cnt(t->l) + 1 + index(t->r, x); }
int rindex(P t, T x) { return !t ? 0 : x >= t->x ? rindex(t->r, x) : cnt(t->r) + 1 + rindex(t->l, x); }
T at(P t, int i) { int u = cnt(t->l); return i == u ? t->x : i < u ? at(t->l, i) : at(t->r, i - ++u); }
void split(P t, T x, P &l, P &r) {
    P u = t ? new Node(*t) : nullptr;
    !t ? void(l = r = 0) : x < t->x ?
    (r = u, split(t->l, x, l, r->l), up(r)) : (l = u, split(t->r, x, l->r, r), up(l));
}
void merge(P &t, P l, P r) {
    !l || !r ? void(t = l ? l : r) : l->p > r->p ?
    (merge(l->r, l->r, r), up(t = l)) : (merge(r->l, l, r->l), up(t = r));
}
void insert(P &t, T x) { P u, v; split(t, x, u, v); merge(u, u, new Node(x)); merge(t, u, v); }
void erase(P &t, T x) {
    if (t) t->x == x ? merge(t, t->l, t->r) :
        (t = new Node(*t), erase(x < t->x ? t->l : t->r, x)), up(t);
}
};


// Luogu. 3369
int main() {
    using namespace PTreap;
    int n;
    scanf("%d", &n);
    vector<P> R;
    R.push_back(nullptr);
    const int INF = 2147483647;
    for (int i = 1; i <= n; i++) {
        int v, o, x;
        scanf("%d%d%d", &v, &o, &x);
        R.push_back(R[v]);
        if (o == 1) insert(R.back(), x);
        else if (o == 2) erase(R.back(), x);
        else if (o == 3) printf("%d\n", index(R.back(), x) + 1);
        else if (o == 4) printf("%d\n", at(R.back(), x - 1));
        else if (o == 5) printf("%d\n", index(R.back(), x) ? at(R.back(), index(R.back(), x) - 1) : -INF);
        else printf("%d\n", rindex(R.back(), x) ? at(R.back(), cnt(R.back()) - rindex(R.back(), x)) : INF);
    }
    return 0;
}
```

## trees/hld.cc

```c++
#include <bits/stdc++.h>
using namespace std;


template <typename T, class ST> struct HLDPoint {
    size_t n;
    vector<int> Size, Dep, Fa, Son, Top, P;
    ST* st;

    HLDPoint(const vector<vector<int>>& G, const vector<T>& A, int root): n(G.size()),
        Size(n, -1), Dep(n, -1), Fa(n, -1), Son(n, -1), Top(n, -1), P(n, -1) {
        function<void(int, int, int)> dfs1 = [&](int u, int p, int dep) {
            Size[u] = 1;
            Dep[u] = dep;
            Fa[u] = p;
            for (auto v : G[u]) {
                if (v != p) {
                    dfs1(v, u, dep + 1);
                    Size[u] += Size[v];
                    if (Son[u] == -1 || Size[v] > Size[Son[u]]) Son[u] = v;
                }
            }
        };
        dfs1(root, -1, 0);
        int ts = 0;
        function<void(int, int, int)> dfs2 = [&](int u, int p, int t) {
            P[u] = ts++;
            Top[u] = t;
            if (Son[u] == -1) return;
            dfs2(Son[u], u, t);
            for (auto v : G[u]) {
                if (v != p && v != Son[u]) dfs2(v, u, v);
            }
        };
        dfs2(root, -1, root);
        vector<T> B(ts);
        for (size_t i = 0; i < A.size(); i++) {
            if (P[i] != -1) {
                B[P[i]] = A[i];
            }
        }
        st = new ST(B);
    }
    void modify(int p, T val) {
        st->modify(P[p], val);
    }
    T query(int x, int y) {
        int tx = Top[x], ty = Top[y];
        if (tx == ty) return Dep[x] <= Dep[y] ? st->query(P[x], P[y] + 1) : query(y, x);
        if (Dep[tx] >= Dep[ty]) return st->op(st->query(P[tx], P[x] + 1), query(Fa[tx], y));
        else return query(y, x);
    }
};

```

## trees/centroid.cc

```c++
#include <bits/stdc++.h>
using namespace std;


void solve(const vector<vector<int>> &G, int root = 1) {
    vector<char> Use(G.size());
    vector<int> Sz(G.size());
    auto find_c = [&](int root) {
        auto dfs = [&](int u, int p, bool b, auto f) -> int {
            if (!b) Sz[u] = 1;
            for (auto v : G[u]) if (v != p && !Use[v]) {
                    if (!b) f(v, u, b, f), Sz[u] += Sz[v];
                    else if (Sz[v] * 2 > Sz[root]) return f(v, u, b, f);
                }
            return u;
        };
        return dfs(root, -1, 0, dfs), dfs(root, -1, 1, dfs);
    };
    auto decompose = [&](int root, auto f) -> void {
        int c = find_c(root);
        Use[c] = 1;
        for (auto u : G[c]) if (!Use[u]) f(u, f);
        // solve
        Use[c] = 0;
    };
    decompose(root, decompose);
}


int main() {
}
```

## matchings/hungary.cc

```c++
#include <bits/stdc++.h>
using namespace std;


vector<int> hungary(const vector<vector<int>> &G) {
    vector<int> M(G.size(), -1);
    vector<char> B(G.size(), 0);
    auto dfs = [&](int u, int p, auto f) -> bool {
        B[u] = 1;
        if (M[u] < 0 && p != -1) return true;
        if (M[u] >= 0 && M[u] != p) return f(M[u], u, f);
        for (auto v : G[u]) if (v != p && !B[v] && f(v, u, f))
                return M[u] = v, M[v] = u, 1;
        return 0;
    };
    for (size_t i = 0; i < G.size(); ++i)
        if (M[i] < 0) fill(B.begin(), B.end(), 0), dfs(i, -1, dfs);
    return M;
}


int main() {
    int n, m, e;
    scanf("%d%d%d", &n, &m, &e);
    vector<vector<int>> G(n + m + 1);
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        if (v > m) continue;
        G[u].push_back(v + n);
        G[v + n].push_back(u);
    }
    auto M = hungary(G);
    int ans = 0;
    for (int i = 1; i <= n; i++) if (M[i] >= 0) ans++;
    printf("%d\n", ans);
    return 0;
}
```

## others/partial_order.cc

```c++
#include <bits/stdc++.h>
using namespace std;


// Luogu. 3810
int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    map<array<int, 3>, int> M;
    vector<array<int, 3>> Q;
    for (int i = 0; i < n; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        M[array<int, 3> {a, b, c}]++;
    }
    int idx = 0;
    vector<int> Dup;
    for (const auto &p : M) {
        Q.emplace_back(p.first);
        Dup.push_back(p.second);
        idx++;
    }
    vector<int> Ans(idx), I(idx), J(idx);
    vector<char> L1(idx), L2(idx);
    iota(I.begin(), I.end(), 0);
    sort(I.begin(), I.end(), [&](int i, int j) { return Q[i] < Q[j]; });
    auto dac1 = [&](int l, int r, auto f1) -> void {
        if (l + 1 >= r) return;
        int m = (l + r) >> 1;
        f1(l, m, f1), f1(m, r, f1);
        for (int i = l; i < r; i++) L1[I[i]] = i >= m;
        inplace_merge(&I[l], &I[m], &I[r], [&](int i, int j) { return Q[i][1] < Q[j][1]; });
        copy(&I[l], &I[r], &J[l]);
        auto dac2 = [&](int l, int r, auto f2) -> void {
            if (l + 1 >= r) return;
            int m = (l + r) >> 1;
            f2(l, m, f2), f2(m, r, f2);
            for (int i = l; i < r; i++) L2[J[i]] = i >= m;
            inplace_merge(&J[l], &J[m], &J[r], [&](int i, int j) { return Q[i][2] < Q[j][2]; });
            int cnt = 0;
            for (int i = l; i < r; i++) {
                int ii = J[i];
                if (!L1[ii] && !L2[ii]) cnt += Dup[ii];
                if (L1[ii] && L2[ii]) Ans[ii] += cnt;
            }
        };
        dac2(l, r, dac2);
    };
    dac1(0, idx, dac1);
    for (int i = 0; i < idx; i++) Ans[i] += Dup[i] - 1;
    vector<int> Cnt(n);
    for (int i = 0; i < idx; i++) Cnt[Ans[i]] += Dup[i];
    for (int i = 0; i < n; i++) printf("%d\n", Cnt[i]);
}
```

## others/inverse_pair.cc

```c++
#include <bits/stdc++.h>
using namespace std;

template <class T> long long inverse_count(const vector<T> &A) {
    auto ninv = 0LL;
    auto B(A);
    auto merge_sort = [&](int l, int r, auto f) -> void {
        if (l + 1 >= r) return;
        int m = (l + r) >> 1;
        f(l, m, f), f(m, r, f);
        for (int u = l, v = m, i = l, c = 0; i < r; i++)
            if (v == r || (u < m && A[u] < A[v])) ninv += c, B[i] = A[u++];
            else c++, B[i] = A[v++];
        copy(&B[l], &B[r], &A[l]);
    };
    merge_sort(0, A.size(), merge_sort);
    return ninv;
}

int main() {
}
```

## others/bitwise.cc

```c++
#include <bits/stdc++.h>
using namespace std;


/* Some useful bitwise operations
 * x & ~(1 << i)            set i-th rightmost bit 0
 * x | (1 << i)             set i-th rightmost bit 1
 * x ^ (1 << i)             flip i-th rightmost bit
 * (x >> i) & 1             get i-th rightmost bit value
 * x & ((1 << i) - 1)       get rightmost i bits
 * x & (x - 1)              set rightmost 1 to 0
 * x | (x + 1)              set rightmost 0 to 1
 * x & -x                   get mask of rightmost 1
 * ~x & (x + 1)             get mask of rightmost 0
 * x | (x - 1)              set rightmost consecutive 0 to 1
 * ((x | (x - 1)) + 1) & x  set rightmost consecutive 1 to 0
 */

/* GCC builtin functions
 * __builtin_ffs(unsigned x)        position of rightmost 1(1-based)
 * __builtin_clz(unsigned x)        number of leading zeros
 * __builtin_ctz(unsigned x)        number of trailing zeros
 * __builtin_popcount(unsigned x)   number of ones
 * __builtin_parity(unsigned x)     odd/even of number of ones
 * for long long type, just add "ll" to function name
 */

// check if x * y will overflow
constexpr bool overflow(long long x, long long y) { return __builtin_clzll(x) + __builtin_clzll(y) <= 64; }
// return next mask with same number of ones
constexpr int next_comb(int m) { int l = m & -m, s = l + m; return s | (m ^ s) / l / 4; }


int main() {
    for (int i = 1; i <= 30; i++)
        printf("%d, %d\n", i, __builtin_ffs(i));
}
```

## others/bit_span.cc

```c++
#include <bits/stdc++.h>
using namespace std;

template <typename T> vector<T> xor_span(const vector<T> &A) {
    auto V(A);
    int k = 0;
    for (int i = 0; i < 8 * (int)sizeof(T); i++) {
        auto p = find_if(&V[k], V.end(), [i](int x) { return x & 1 << i; });
        if (p == V.end()) continue;
        swap(V[k], *p);
        for (int j = 0; j < (int)V.size(); j++)
            if (j != k && (V[j] & 1 << i)) V[j] ^= V[k];
        k++;
    }
    V.resize(k);
    return V;
}


int main() {
}
```

## others/geometry.cc

```c++
#include <bits/stdc++.h>
using namespace std;

using Num = double;
// using Num = long long;
constexpr Num EPS = 1e-9, MAGIC = 2.1415927e18, PI = acos(-1);

constexpr Num sqr(Num a) { return a * a; }
constexpr Num cmp(Num a, Num b) { return (1 + fabs(a)) * EPS < fabs(a - b) ? a - b : 0; }

struct Vec { Num x, y; } NOVEC = {MAGIC, MAGIC};
struct Ray { Vec u, v; } NORAY = {NOVEC, NOVEC};
struct Cir { Vec u; Num r; } NOCIR = {NOVEC, MAGIC};

constexpr Num sqr(Vec a) { return sqr(a.x) + sqr(a.y); }
constexpr Num abs(Vec a) { return sqrt(sqr(a)); }
constexpr Num cmp(Vec a, Vec b) { Num at = cmp(a.x, b.x); return !at ? cmp(a.y, b.y) : at; }

constexpr Vec operator *(Num u, Vec a) { return {a.x * u, a.y * u}; }
constexpr Vec operator *(Vec a, Num u) { return {a.x * u, a.y * u}; }
constexpr Vec operator /(Vec a, Num u) { return {a.x / u, a.y / u}; }
constexpr Vec operator +(Vec a, Vec b) { return {a.x + b.x, a.y + b.y}; }
constexpr Vec operator -(Vec a, Vec b) { return {a.x - b.x, a.y - b.y}; }
constexpr Num operator *(Vec a, Vec b) { return cmp(a.x * b.y, +a.y * b.x); }
constexpr Num operator %(Vec a, Vec b) { return cmp(a.x * b.x, -a.y * b.y); }
constexpr bool operator <(Vec a, Vec b) { return cmp(a, b) < 0; }
constexpr bool operator==(Vec a, Vec b) { return cmp(a, b) == 0; }
constexpr bool between(Num a, Num b, Num c) { return min(b, c) <= a && a <= max(b, c); }



// Care for overflow
constexpr Vec intersect(Ray a, const Ray& b) {
    Vec t = a.u - a.v, s = b.u - b.v;
    Num o = s * t;
    if (!o) return NOVEC;
    return a.u + (a.u - b.u) * s * t / o;
}

constexpr int relation(Vec p, Ray l) {
    if ((p - l.u) * (p - l.v)) return 0;
    return between(p.x, l.u.x, l.u.y) && between(p.y, l.u.y, l.v.y) ? 2 : 1;
}


vector<Vec> convex_hull(vector<Vec> A) {
    sort(A.begin(), A.end());
    A.erase(unique(A.begin(), A.end()), A.end());
    if (A.size() < 3u) return A;
    vector<Vec> C;
    for (size_t i = 0, o = 1, m = 1; ~i; i += o) {
        while (C.size() > m) {
            Vec a = C[C.size() - 2u] - C.back();
            Vec b = A[i] - C.back();
            if (a * b < 0) break;
            C.pop_back();
        }
        C.push_back(A[i]);
        if (i + 1u == A.size()) m = C.size(), o = -1;
    }
    C.pop_back();
    return C;
}


int main() {
    return 0;
}
```

