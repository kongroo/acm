#include <bits/stdc++.h>
using namespace std;

struct EulerGraph : public vector<vector<int>> {
  struct Edge {
    int u, v;
  };
  const bool dir;
  vector<Edge> edges;
  vector<unsigned> ind;
  EulerGraph(int n, bool dir = false) : vector<vector<int>>(n), dir(dir), ind(n) {}

  void add_edge(int u, int v) {
    edges.push_back({u, v});
    at(u).push_back(edges.size());
    ind[v]++;
    if (!dir) {
      edges.push_back({v, u});
      at(v).push_back(edges.size());
      ind[u]++;
    }
  }
  vector<int> euler_path(int start) {
    vector<char> valid(edges.size(), 1);
    vector<int> ans;
    auto dfs = [&](int u, auto f) -> void {
      for (int i : at(u)) {
        if (!valid[i]) continue;
        valid[i] = 0;
        if (!dir) valid[i ^ 1] = 0;
        f(edges[i].v, f);
      }
      ans.push_back(u);
    };
    dfs(start, dfs);
    return ans;
  }
};

int main() {
  
}
