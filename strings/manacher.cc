#include <bits/stdc++.h>
using namespace std;


vector<int> manacher(const string& s) {
    int n = int(s.size());
    vector<int> Ans(n + n + 1, 1);
    for (int i = 1, x = 0; i < int(Ans.size()); i++) {
        Ans[i] = max(x + Ans[x] - i, 1 - i % 2);
        if (x + x >= i) Ans[i] = min(Ans[i], Ans[x + x - i]);
        int a = (i - 1 - Ans[i]) / 2, b = (i + 1 + Ans[i]) / 2;
        while (a >= 0 && b < n && s[a] == s[b]) a--, b++, Ans[i] += 2;
        if (i + Ans[i] > x + Ans[x]) x = i;
    }
    return Ans;
}


int main() {

}
