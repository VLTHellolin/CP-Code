// Hellolin v4.8.0

// clang-format off
#include <bits/stdc++.h>
#ifdef LOCAL
#include "hellolin/a/debug_tools.hpp"
#endif
using namespace std;
namespace hellolin {
using int64 = long long; using uint64 = unsigned long long; using comp = complex<double>;
template <class T> bool chmax(T &x, T y) { return y > x ? x = y, 1 : 0; }
template <class T> bool chmin(T &x, T y) { return y < x ? x = y, 1 : 0; }
class IO {
private:
  static constexpr int Buffer = 1<<19;
  char ib[Buffer], ob[Buffer], *is, *it, *os = ob, *ot = ob + Buffer - 1; FILE *inf, *ouf; vector<string> dt;
  void fl() { fwrite(ob, 1, os - ob, ouf), os = ob; }
  char gc() { return is == it && ((it = (is = ib) + fread(ib, 1, Buffer, inf)), is == it) ? EOF : *is++; }
  void pc(char x) { ((*os++ = x, os) == ot) ? fl() : void(); }
  template <class T> void up(T x) { dt.push_back(to_string(x)); } template <class T, class...A> void up(T x, A...a) { up(x), up(a...); }
public:
  void flush() { fl(), fflush(ouf); } IO(FILE *_i = stdin, FILE *_o = stdout) : inf(_i), ouf(_o) {} ~IO() { flush(); }
  void reopen(FILE *_i = stdin, FILE *_o = stdout) { flush(); inf = _i, ouf = _o; }
  void reopen(const char *i, const char *o) { FILE *_i = fopen(i, "r"), *_o = fopen(o, "w"); reopen(_i, _o); }
  template <class T> void input(T &x) {
    x = 0; bool f = 0; char c = gc(); while (!isdigit(c)) f ^= c == '-', c = gc();
    while (isdigit(c)) x = x * 10 + c - 48, c = gc(); x = f ? -x : x;
  }
  void input(char &x) { do { x = gc(); } while (!isgraph(x)); } void input(char *x) { char c = gc(); while (isgraph(c)) *x++ = c, c = gc(); *x++ = '\0'; }
  void input(string &x) { char c = gc(); x = ""; while (isgraph(c)) x += c, c = gc(); }
  template <class T, class...A> void input(T &x, A &...a) { input(x), input(a...); }
  template <class T> void write(T x) { if (x < 0) pc('-'), x = -x; if (x > 9) write(x / 10); pc(x % 10 + 48); }
  void write(char x) { pc(x); } void write(const char *x) { size_t l = strlen(x); for (size_t i = 0; i < l; ++i) pc(x[i]); }
  void write(const string &x) { for(const char &i : x) pc(i); }
  template <class T, class...A> void write(T x, A...a) { write(x), write(a...); }
  template <class...A> void print(const string &x, A...a) {
    dt.clear(); up(a...); string r = ""; int tp = 0;
    for (size_t i = 0; i < x.size(); ++i) if (x[i] == '%') r += dt[tp++]; else r += x[i];
    write(r);
  }
} io;
void main();
} // namespace hellolin
int main() {
#ifndef LOCAL
  // hellolin::io.reopen(".in", ".out");
#endif
  hellolin::main();
}
// clang-format on

namespace hellolin {
static constexpr int N = 1040;
int64 n, k, ans;
int64 a[N][N], x[N][N], y[N][N], z[N][N], w[N][N];
void main() {
  io.input(n, k);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) {
      io.input(a[i][j]);
      a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
    }
  for (int i = n; i >= k; --i)
    for (int j = n; j >= k; --j)
      a[i][j] -= a[i - k][j] + a[i][j - k] - a[i - k][j - k];
  for (int i = k; i <= n; ++i)
    for (int j = k; j <= n; ++j)
      x[i][j] = max(a[i][j], max(x[i - 1][j], x[i][j - 1]));
  for (int i = k; i <= n; ++i)
    for (int j = n; j >= k; --j)
      y[i][j] = max(a[i][j], max(y[i - 1][j], y[i][j + 1]));
  for (int i = n; i >= k; --i)
    for (int j = k; j <= n; ++j)
      z[i][j] = max(a[i][j], max(z[i + 1][j], z[i][j - 1]));
  for (int i = n; i >= k; --i)
    for (int j = n; j >= k; --j)
      w[i][j] = max(a[i][j], max(w[i + 1][j], w[i][j + 1]));

  for (int i = k; i <= n - k; ++i)
    for (int j = k; j <= n - k; ++j)
      chmax(ans, x[i][j] + y[i][j + k] + z[i + k][n]);
  for (int i = k; i <= n - k; ++i)
    for (int j = k; j <= n - k; ++j)
      chmax(ans, x[i][n] + z[i + k][j] + w[i + k][j + k]);
  for (int i = k; i <= n - k; ++i)
    for (int j = k; j <= n - k; ++j)
      chmax(ans, x[i][j] + y[n][j + k] + z[i + k][j]);
  for (int i = k; i <= n - k; ++i)
    for (int j = k; j <= n - k; ++j)
      chmax(ans, x[n][j] + y[i][j + k] + w[i + k][j + k]);
  for (int i = k * 2; i <= n - k; ++i)
    for (int j = k; j <= n - k; ++j)
      chmax(ans, a[i][j] + x[i - k][n] + z[i + k][n]);
  for (int i = k; i <= n - k; ++i)
    for (int j = k * 2; j <= n - k; ++j)
      chmax(ans, a[i][j] + x[n][j - k] + y[n][j + k]);

  io.write(ans);
}
} // namespace hellolin