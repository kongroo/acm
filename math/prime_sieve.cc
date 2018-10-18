#include <bits/stdc++.h>
using namespace std;


vector<int> prime_sieve(int n) {
    vector<int> Pr, Low(n);
    Low[1] = 1;
    for (int x = 2; x < n; x++) {
        if (!Low[x]) Pr.push_back(Low[x] = x);
        for (auto p : Pr) {
            if (x * p >= n) break;
            Low[x * p] = p;
            if (x % p == 0) break;
        }
    }
    return Pr;
}


int main() {
    return 0;
}
