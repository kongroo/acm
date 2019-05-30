#include <bits/stdc++.h>
using namespace std;

/* Some useful bitwise operations
 * x & ~(1 << i)            set i-th rightmost bit 0
 * x | (1 << i)             set i-th rightmost bit 1
 * x ^ (1 << i)             flip i-th rightmost bit
 * (x >> i) & 1             get i-th rightmost bit value
 * x & ((1 << i) - 1)       get rightmost i bits
 * x & (x - 1)              set rightmost 1 to 0
 * x | (x + 1)              set rightmost 0 to 1
 * x & -x                   get mask of rightmost 1
 * ~x & (x + 1)             get mask of rightmost 0
 * x | (x - 1)              set rightmost consecutive 0 to 1
 * ((x | (x - 1)) + 1) & x  set rightmost consecutive 1 to 0
 */

/* GCC builtin functions
 * __builtin_ffs(unsigned x)        position of rightmost 1(1-based)
 * __builtin_clz(unsigned x)        number of leading zeros
 * __builtin_ctz(unsigned x)        number of trailing zeros
 * __builtin_popcount(unsigned x)   number of ones
 * __builtin_parity(unsigned x)     odd/even of number of ones
 * for long long type, just add "ll" to function name
 */

// check if x * y will overflow
constexpr bool overflow(long long x, long long y) {
  return __builtin_clzll(x) + __builtin_clzll(y) <= 64;
}
// return next mask with same number of ones
constexpr int next_comb(int m) {
  int l = m & -m, s = l + m;
  return s | (m ^ s) / l / 4;
}

int main() {
  for (int i = 1; i <= 30; i++) printf("%d, %d\n", i, __builtin_ffs(i));
}
