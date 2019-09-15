#include <bits/stdc++.h>
using namespace std;

template <typename T> T eval(const string &s) {
}

int main() {
  int x;
  cin >> x;
  cout << eval<double>("3.1415926 * -1.5") << endl;
  cout << eval<int>("100 * 1000 + 1") << endl;
  cout << eval<long long>("1000000007 * 100000007 + 5342 / 23 + 7") << endl;
  cout << eval<int>("3.1415926 * -1.5") << endl;
  cout << eval<double>("3.1415926 * -1.5") << endl;
}
