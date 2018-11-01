#include <bits/stdc++.h>
#include <ext/rope>
using namespace std;
using namespace __gnu_cxx;


// rope is used for insert, delete, access at O(n*sqrt(n))
int main() {
    rope<int> t;
    t.push_back(1);
    t.push_front(2);
    t.insert(1, 3);
    t.erase(2);
    t.replace(0, 5);
    t.substr(0, 2);
    t.at(2);
    t.clear();
}
