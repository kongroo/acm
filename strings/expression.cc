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
