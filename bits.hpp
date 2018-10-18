#include <bits/stdc++.h>
using namespace std;

template <typename T> vector<T> xor_span(const vector<T>& A) {
    auto V(A);
    int k = 0;
    for (int i = 0; i < 8 * (int)sizeof(T); i++) {
        auto p = find_if(V.begin() + k, V.end(), [i](int x) {
            return bool(x & (1 << i));
        });
        if (p == V.end()) continue;
        swap(V[k], *p);
        for (int j = 0; j < (int)V.size(); j++) {
            if (j != k && (V[j] & 1 << i)) V[j] ^= V[k];
        }
        k++;
    }
    V.resize(k);
    return V;
}
