#include <bits/stdc++.h>
using namespace std;


int find_centroid(const vector<vector<int>> &G, int root = 0,
                  const vector<bool> &Dead = vector<bool>()) {
    static vector<int> size(G.size());
    function<void (int, int)> calcSize = [&](int u, int p) {
        size[u] = 1;
        for (auto v : G[u]) if (v != p && (Dead.empty() || !Dead[v]))
                calcSize(v, u), size[u] += size[v];
    };
    calcSize(root, -1);
    int n = size[root];
    function<int (int, int)> dfs = [&](int u, int p) {
        for (auto v : G[u]) if (v != p && (Dead.empty() || !Dead[v]))
                if (size[v] > n / 2) return dfs(v, u);
        return u;
    };
    return dfs(root, -1);
}

/*
vector<LL> solve(const vector<vector<int>>& G, const vector<int> B) {
    vector<LL> Ans(G.size());
    vector<bool> Dead(G.size());
    vector<LL> Cnt(1 << 20, 0);
    function<void (int)> decompose = [&](int root) {
        int c = findCentroid(G, root, Dead);
        Dead[c] = true;
        // solve subtrees of centroid
        for (auto u : G[c]) if (!Dead[u]){
            decompose(u);
        }
        // solve paths with centroid
        function<void(int, int, int, int)> updateCnt = [&](int u, int p, int mask, int val) {
            mask ^= B[u];
            Cnt[mask] += val;
            for (auto v: G[u]) if (v != p && !Dead[v]) {
                updateCnt(v, u, mask, val);
            }
        };
        function<LL (int, int, int)> updateAns = [&](int u, int p, int mask) {
            mask ^= B[u];
            LL ret = Cnt[mask];
            for (int i=0;i<20;i++) {
                ret += Cnt[(1<<i) ^ mask];
            }
            for (auto v: G[u]) if (v != p && !Dead[v]) {
                ret += updateAns(v, u, mask);
            }
            Ans[u] += ret;
            return ret;
        };
        // calc cnts of paths start from centroid
        updateCnt(c, -1, 0, 1);
        // all palindrome paths start from centroid
        LL ans = Cnt[0];
        for (int i=0;i<20;i++) {
            ans += Cnt[1 << i];
        }
        // all palindrome paths start in subtree and pass centroid
        for (auto u: G[c]) if (!Dead[u]) {
            // remove current subtree
            updateCnt(u, c, B[c], -1);
            ans += updateAns(u, c, 0);
            // restore current subtree
            updateCnt(u, c, B[c], 1);
        }
        Ans[c] += ans / 2; // remove duplicate
        updateCnt(c, -1, 0, -1);
        Dead[c] = false;
    };
    decompose(1);
    return Ans;
}
*/
