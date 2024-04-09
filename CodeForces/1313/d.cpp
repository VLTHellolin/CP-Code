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
static constexpr int N = 2e5 + 5, M = 1e9 + 5, K = 8;
int n, m, k, l[N], r[N], ans, cnt[1 << K];
vector<int> pt, sg[N], prev, curr;
int dp[N][1 << K];
void main() {
  io.input(n, m, k);
  pt.emplace_back(-1);
  for (int i = 1; i <= n; ++i) {
    io.input(l[i], r[i]);
    pt.emplace_back(l[i]);
    pt.emplace_back(++r[i]);
  }
  sort(pt.begin(), pt.end());
  pt.erase(unique(pt.begin(), pt.end()), pt.end());
  for (int i = 1; i <= n; ++i) {
    l[i] = lower_bound(pt.begin(), pt.end(), l[i]) - pt.begin();
    r[i] = lower_bound(pt.begin(), pt.end(), r[i]) - pt.begin();
  }
  for (int i = 1; i <= n; ++i)
    for (int j = l[i]; j < r[i]; ++j)
      sg[j].emplace_back(i);
  for (int i = 1; i < (int) pt.size() - 1; ++i) {
    prev.clear();
    curr.clear();
    int l1 = sg[i - 1].size(), l2 = sg[i].size();
    for (int j = 0; j < l1; ++j)
      for (int k = 0; k < l2; ++k)
        if (sg[i - 1][j] == sg[i][k]) {
          prev.emplace_back(j);
          curr.emplace_back(k);
        }
    memset(cnt, 0, sizeof(cnt));
    l1 = 1 << l1, l2 = 1 << l2;
    for (int j = 0; j < l1; ++j) {
      int temp = 0;
      for (int k = 0; k < (int) prev.size(); ++k)
        temp |= (j >> prev[k] & 1) << k;
      chmax(cnt[temp], dp[i - 1][j]);
    }
    for (int j = 0; j < l2; ++j) {
      int temp = 0;
      for (int k = 0; k < (int) curr.size(); ++k)
        temp |= (j >> curr[k] & 1) << k;
      // chmax(dp[i][j], cnt[temp] + (popcount((unsigned) j) & 1) * (pt[i + 1] - pt[i]));
      chmax(dp[i][j], cnt[temp] + (__builtin_popcount(j) & 1) * (pt[i + 1] - pt[i]));
      chmax(ans, dp[i][j]);
    }
  }
  io.write(ans);
}
} // namespace hellolin