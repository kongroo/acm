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
