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
  template <class T> void input(T &x) {
    x = 0; bool f = 0; char c = gc(); while (!isdigit(c)) f ^= c == '-', c = gc();
    while (isdigit(c)) x = x * 10 + c - 48, c = gc(); x = f ? -x : x;
  }
  void input(char &x) { x = gc(); } void input(char *x) { char c = gc(); while (isgraph(c)) *x++ = c, c = gc(); *x++ = '\0'; }
  void input(string &x) { char c = gc(); x = ""; while (isgraph(c)) x += c; }
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
static constexpr int N = 114, M = 5e5 + 5;
int n, m, w;
int64 ans, req;
long double fl_ans;
struct company {
  int w, c, a;
  long double f;
  // bool operator<(const company &x) const { return f < x.f; }
} p[M];
int num[M];
void main() {
  io.input(n, m, w);
  for (int i = 1; i <= m; ++i)
    io.input(p[i].w);
  for (int i = 1; i <= m; ++i)
    io.input(p[i].c);
  for (int i = 1; i <= m; ++i)
    io.input(p[i].a);
  for (int j = 1; j <= n; ++j) {
    for (int i = 1; i <= m; ++i) {
      p[i].f = (long double) p[i].c / p[i].w;
      num[i] = i;
    }
    int l = 1, r = m;
    req = w;
    while (l < r) {
      int mid = (l + r) >> 1;
      nth_element(&num[l], &num[mid], &num[r + 1], [&](const int &x, const int &y) { return p[x].f < p[y].f; });
      int64 pri = 0, cnt = 0;
      for (int i = l; i <= mid; ++i) {
        cnt += p[num[i]].w;
        pri += p[num[i]].c;
      }
      if (cnt <= req) {
        l = mid + 1;
        req -= cnt;
        ans += pri;
      } else
        r = mid;
    }
    long double rst = req * p[num[l]].f;
    ans += (int64) rst;
    fl_ans += rst - (int64) rst;
    for (int i = 1; i <= m; ++i)
      p[i].c -= p[i].a;
  }
  ans += (int64) fl_ans;
  fl_ans -= (int64) fl_ans;
  io.write(ans, '.');
  for (int i = 1; i <= 12; ++i) {
    fl_ans *= 10;
    io.write((int) fl_ans);
    fl_ans -= (int) fl_ans;
  }
}
} // namespace hellolin