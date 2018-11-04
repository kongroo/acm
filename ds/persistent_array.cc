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
