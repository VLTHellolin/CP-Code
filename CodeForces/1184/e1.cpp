// ****************************** //
//    Hellolin's Code Template    //
//             v4.7.0             //
// ****************************** //

// NOLINTBEGIN
// clang-format off
#include <bits/stdc++.h>
#ifdef LOCAL
#include "hellolin/a/debug_tools.hpp"
#endif
using namespace std;
namespace hellolin {
using int64 = long long; using uint64 = unsigned long long; using comp = complex<double>;
mt19937_64 mtrng(chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now().time_since_epoch()).count());
template <class T> T rnd(T l, T r) { return std::uniform_int_distribution<T>(l, r)(mtrng); }
template <class T> bool chmax(T &x, T y) { return y > x ? x = y, 1 : 0; }
template <class T> bool chmin(T &x, T y) { return y < x ? x = y, 1 : 0; }
template <class T> T pow(T x, int64 y, T m) { T r = 1; for (; y; y >>= 1, (x *= x) %= m) (y & 1) && ((r *= x) %= m); return r; }
template <class T> T inv(T x, T m) { return pow(x, m - 2, m); }
template <class T, const T M>
struct Z { T x; Z(T y = 0) { x = y % M, x < 0 && (x += M); }
  friend Z operator+(Z a, Z b) { return ((a.x += b.x) >= M && (a.x -= M)), a; } friend Z operator-(Z a, Z b) { return ((a.x -= b.x) < 0 && (a.x += M)), a; }
  friend Z operator*(Z a, Z b) { return a.x * b.x % M; } friend Z operator/(Z a, Z b) { return a.x * inv(b.x, M) % M; }
  Z &operator+=(Z a) { return (x += a.x) >= M && (x -= M), *this; } Z &operator-=(Z a) { return (x -= a.x) < 0 && (x += M), *this; }
  Z &operator*=(Z a) { return x = x * a.x % M, *this; } Z &operator/=(Z a) { return x = x * inv(a.x, M) % M, *this; }
};
void main();
} // namespace hellolin
int main() {
#ifndef LOCAL
  // freopen(".in", "r", stdin);
  // freopen(".out", "w", stdout);
#endif
  cin.tie(nullptr)->sync_with_stdio(false);
  hellolin::main();
}
// NOLINTEND
// clang-format on

namespace hellolin {
static constexpr int N = 1e5 + 5, M = 1e6 + 5;
int n, m, fa[N];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
struct edge {
  int x, y, z;
  bool operator<(const edge &x) const {
    return z < x.z;
  }
} e[M];
void main() {
  cin >> n >> m;
  for (int i = 1, x, y, z; i <= m; ++i) {
    cin >> x >> y >> z;
    e[i] = {x, y, z};
  }
  sort(&e[2], &e[m + 1]);
  for (int i = 1; i <= n; ++i)
    fa[i] = i;
  for (int i = 2; i <= m; ++i) {
    const auto &[x, y, z] = e[i];
    int fx = find(x), fy = find(y);
    if (fx == fy) continue;
    fa[fy] = fx;
    if (find(e[1].x) == find(e[1].y)) {
      cout << z << '\n';
      return;
    }
  }
  cout << (int) 1e9 << '\n';
}
} // namespace hellolin