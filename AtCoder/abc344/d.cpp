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
static constexpr int N = 109, M = 15;
string t, p;
int n, l, ans;
// unordered_map<string, bool> a[N];
int f[N][N];
void main() {
  cin >> t >> n;
  l = t.size();
  // for (int i = 1; i <= n; ++i) {
  //   cin >> m[i];
  //   for (int j = 1; j <= m[i]; ++j) {
  //     cin >> p;
  //     a[i][p] = true;
  //   }
  // }
  for (int i = 0; i <= n; ++i)
    for (int j = 1; j <= l; ++j)
      f[i][j] = N;
  f[0][0] = 0;
  for (int i = 1, m; i <= n; ++i) {
    cin >> m;
    for (int j = 0; j <= l; ++j)
      f[i][j] = f[i - 1][j];
    for (int _ = 1; _ <= m; ++_) {
      cin >> p;
      for (int j = p.size(); j <= l; ++j) {
        bool fl = true;
        for (int k = 0; k < (int) p.size(); ++k)
          if (p[k] != t[j + k - p.size()]) {
            fl = false;
            break;
          }
        if (fl) {
          chmin(f[i][j], f[i - 1][j - p.size()] + 1);
        }
      }
    }
  }
  if (f[n][l] == N) f[n][l] = -1;
  cout << f[n][l] << '\n';
}
} // namespace hellolin