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
static constexpr int N = 2e5 + 5;
static constexpr int64 P = 1e9 + 7, Q = 5e8 + 4;
int n, rt;
int64 *ptr, *mp[N], ans;
int len[N], dep[N], son[N];
int64 res[N];
template <class T>
T pow(T x, int64 y) {
  T r = 1;
  for (; y; (x *= x) %= P, y >>= 1)
    (y & 1) && ((r *= x) %= P);
  return r;
}
void main() {
  io.input(n);
  vector<vector<int>> g(n + 5);
  function<void(int)> dfs1 = [&](int u) {
    for (const int &v : g[u]) {
      dep[v] = dep[u] + 1;
      dfs1(v);
      chmax(len[u], len[v] + 1);
      if (len[v] > len[son[u]]) son[u] = v;
    }
  };
  function<void(int)> dfs2 = [&](int u) {
    int curr = 0;
    mp[u][dep[u]] = Q;
    if (!son[u]) return;
    mp[son[u]] = mp[u];
    dfs2(son[u]);
    for (const int &v : g[u]) {
      if (v != son[u]) {
        chmax(curr, len[v]);
        mp[v] = ptr - dep[v];
        ptr += len[v] + 1;
        dfs2(v);
      }
    }
    for (int i = dep[u] + 1; i <= dep[u] + 1 + curr; ++i)
      res[i] = ((1 - mp[u][i]) % P + P) % P;
    for (const int &v : g[u]) {
      if (v != son[u]) {
        for (int i = dep[v]; i <= dep[v] + len[v]; ++i) {
          int64 nxt = ((1 - mp[v][i]) % P + P) % P;
          mp[u][i] = (res[i] * mp[v][i] % P + nxt * mp[u][i] % P) % P;
          // we should be able to calc v res...
          (res[i] *= nxt) %= P;
        }
      }
    }
  };
  for (int i = 2, x; i <= n + 1; ++i) {
    io.input(x);
    g[++x].emplace_back(i);
  }
  len[rt = 0] = -1;
  ptr = new int64[N];
  mp[1] = ptr;
  dfs1(1);
  ptr += len[1] + 1;
  dfs2(1);
  for (int i = 0; i <= len[1]; ++i)
    (ans += mp[1][i]) %= P;
  io.write(ans * pow(2ll, n + 1) % P);
}
} // namespace hellolin