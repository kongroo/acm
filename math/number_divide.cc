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
