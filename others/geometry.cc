#include <bits/stdc++.h>
using namespace std;

using Num = double;
// using Num = long long;
constexpr Num EPS = 1e-9, MAGIC = 2.1415927e18, PI = acos(-1);

constexpr Num sqr(Num a) { return a * a; }
constexpr Num cmp(Num a, Num b) { return (1 + fabs(a)) * EPS < fabs(a - b) ? a - b : 0; }

struct Vec {
  Num x, y;
} NOVEC = {MAGIC, MAGIC};
struct Ray {
  Vec u, v;
} NORAY = {NOVEC, NOVEC};
struct Cir {
  Vec u;
  Num r;
} NOCIR = {NOVEC, MAGIC};

constexpr Num sqr(Vec a) { return sqr(a.x) + sqr(a.y); }
constexpr Num abs(Vec a) { return sqrt(sqr(a)); }
constexpr Num cmp(Vec a, Vec b) {
  Num at = cmp(a.x, b.x);
  return !at ? cmp(a.y, b.y) : at;
}

constexpr Vec operator*(Num u, Vec a) { return {a.x * u, a.y * u}; }
constexpr Vec operator*(Vec a, Num u) { return {a.x * u, a.y * u}; }
constexpr Vec operator/(Vec a, Num u) { return {a.x / u, a.y / u}; }
constexpr Vec operator+(Vec a, Vec b) { return {a.x + b.x, a.y + b.y}; }
constexpr Vec operator-(Vec a, Vec b) { return {a.x - b.x, a.y - b.y}; }
constexpr Num operator*(Vec a, Vec b) { return cmp(a.x * b.y, +a.y * b.x); }
constexpr Num operator%(Vec a, Vec b) { return cmp(a.x * b.x, -a.y * b.y); }
constexpr bool operator<(Vec a, Vec b) { return cmp(a, b) < 0; }
constexpr bool operator==(Vec a, Vec b) { return cmp(a, b) == 0; }
constexpr bool between(Num a, Num b, Num c) { return min(b, c) <= a && a <= max(b, c); }

// Care for overflow
constexpr Vec intersect(Ray a, const Ray& b) {
  Vec t = a.u - a.v, s = b.u - b.v;
  Num o = s * t;
  if (!o) return NOVEC;
  return a.u + (a.u - b.u) * s * t / o;
}

constexpr int relation(Vec p, Ray l) {
  if ((p - l.u) * (p - l.v)) return 0;
  return between(p.x, l.u.x, l.u.y) && between(p.y, l.u.y, l.v.y) ? 2 : 1;
}

vector<Vec> convex_hull(vector<Vec> A) {
  sort(A.begin(), A.end());
  A.erase(unique(A.begin(), A.end()), A.end());
  if (A.size() < 3u) return A;
  vector<Vec> C;
  for (size_t i = 0, o = 1, m = 1; ~i; i += o) {
    while (C.size() > m) {
      Vec a = C[C.size() - 2u] - C.back();
      Vec b = A[i] - C.back();
      if (a * b < 0) break;
      C.pop_back();
    }
    C.push_back(A[i]);
    if (i + 1u == A.size()) m = C.size(), o = -1;
  }
  C.pop_back();
  return C;
}

int main() { return 0; }
