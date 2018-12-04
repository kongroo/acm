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
