// Hellolin v4.8.2

// clang-format off
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
// #include <tuple>
#ifdef LOCAL
#include "hellolin/all/debug_tools.hpp"
#endif
using namespace std;
namespace hellolin {
// using int64 = long long; using uint64 = unsigned long long; using real32 = double; using real64 = long double;
// using comp = complex<real32>; template <class T> using spair = pair<T, T>;
// #define cTr const T&
// template <class T> bool chmax(T &x, cTr y) { return y > x ? x = y, 1 : 0; }
// template <class T> bool chmin(T &x, cTr y) { return y < x ? x = y, 1 : 0; }
// template <class T> bool range(cTr l, cTr r, cTr x) { return l <= x && x <= r; }
// template <class T> bool range(cTr l, cTr r, cTr x, cTr y) { return l <= x && x <= y && y <= r; }
// #undef cTr
// class IO {
// private:
//   static constexpr int Buffer = 1<<19; char ib[Buffer], ob[Buffer], *is, *it, *os = ob, *ot = ob + Buffer - 1; FILE *inf, *ouf; vector<string> dt;
//   void fl() { fwrite(ob, 1, os - ob, ouf), os = ob; } void pc(char x) { ((*os++ = x, os) == ot) ? fl() : void(); }
//   char gc() { return is == it && ((it = (is = ib) + fread(ib, 1, Buffer, inf)), is == it) ? EOF : *is++; }
//   template <class T> void up(T x) { dt.push_back(to_string(x)); } template <class T, class...A> void up(T x, A...a) { up(x), up(a...); }
// public:
//   void flush() { fl(), fflush(ouf); } IO(FILE *_i = stdin, FILE *_o = stdout) : inf(_i), ouf(_o) {} ~IO() { flush(); }
//   void reopen(FILE *_i = stdin, FILE *_o = stdout) { flush(); inf = _i, ouf = _o; }
//   void reopen(const char *i, const char *o) { FILE *_i = fopen(i, "r"), *_o = fopen(o, "w"); reopen(_i, _o); }
//   template <class T> void input(T &x) {
//     x = 0; bool f = 0; char c = gc(); while (!isdigit(c)) f ^= c == '-', c = gc(); while (isdigit(c)) x = x * 10 + c - 48, c = gc(); x = f ? -x : x;
//   }
//   void input(char &x) { do { x = gc(); } while (!isgraph(x)); } void input(char *x) { char c = gc(); while (isgraph(c)) *x++ = c, c = gc(); *x++ = '\0'; }
//   void input(string &x) { char c = gc(); x = ""; while (isgraph(c)) x += c, c = gc(); }
//   template <class T, class...A> void input(T &x, A &...a) { input(x), input(a...); } template <class T1, class T2> void input(pair<T1, T2> &x) { input(x.first, x.second); }
//   template <class T> void write(T x) { if (x < 0) pc('-'), x = -x; if (x > 9) write(x / 10); pc(x % 10 + 48); }
//   void write(char x) { pc(x); } void write(const char *x) { size_t l = strlen(x); for (size_t i = 0; i < l; ++i) pc(x[i]); }
//   void write(const string &x) { for(const char &i : x) pc(i); } template <class T, class...A> void write(T x, A...a) { write(x), write(a...); }
//   template <class...A> void print(const string &x, A...a) {
//     dt.clear(); up(a...); string r = ""; int tp = 0; for (size_t i = 0; i < x.size(); ++i) if (x[i] == '%') r += dt[tp++]; else r += x[i]; write(r);
//   }
// } io;
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
// static constexpr int N = 1010, M = 600;
const int N = 1010, M = 605;
int n, x, y, m, k, temp;
string tmp;
int fa[M], f[M][M], siz[2][M];
bool ok[M], F[M];
// int find(int x) { return x == fa[x] ? x : (F[x] ^= F[fa[x]], fa[x] = find(fa[x])); }
int find(int x) {
  if (x == fa[x]) return x;
  int y = find(fa[x]);
  F[x] ^= F[fa[x]];
  return fa[x] = y;
}
void merge(int u_, int v_, bool w) {
  int u = find(u_), v = find(v_);
  if (u != v) {
    fa[u] = v;
    F[u] = F[u_] ^ F[v_] ^ w;
    siz[0][v] += siz[F[u]][u];
    siz[1][v] += siz[!F[u]][u];
  }
}
void main() {
  // cin.tie(nullptr)->sync_with_stdio(false);
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  while (cin >> n >> x >> y, n + x + y) {
    // vector<tuple<int, int, int>> K;
    vector<int> k1, k2, num;
    m = x + y;
    for (int i = 1; i <= m; ++i) {
      fa[i] = i;
      siz[0][i] = 1, siz[1][i] = 0;
      ok[i] = F[i] = false;
    }
    memset(f, 0, sizeof(f));
    for (int i = 1, u, v, w; i <= n; ++i) {
      cin >> u >> v >> tmp;
      w = tmp == "no";
      merge(u, v, w);
    }
    k = 0;
    for (int i = 1; i <= m; ++i)
      if (find(i) == i) {
        // cerr<<i<<'\n';
        // K.emplace_back(i, siz[0][i], siz[1][i]);
        k1.push_back(siz[0][i]);
        k2.push_back(siz[1][i]);
        num.push_back(i);
        ++k;
      }
    // cerr<<'\n';
    f[0][0] = 1;
    for (int i = 1; i <= k; ++i) {
      // const auto &[I, K1, K2] = K[i - 1];
      const int &K1 = k1[i - 1], &K2 = k2[i - 1];
      for (int j = min(K1, K2); j <= x; ++j)
        f[i][j] += f[i - 1][j - K1] + f[i - 1][j - K2];
    }
    if (f[k][x] != 1) {
      cout << "no\n";
      continue;
    }
    for (int j = x, i = k; i; --i) {
      // const auto &[I, K1, K2] = K[i - 1];
      const int &K1 = k1[i - 1], &K2 = k2[i - 1], &I = num[i - 1];
      if (f[i - 1][j - K1]) {
        j -= K1;
        ok[I] = false;
      } else if (f[i - 1][j - K2]) {
        j -= K2;
        ok[I] = true;
      }
    }
    for (int i = 1; i <= m; ++i) {
      if (ok[find(i)] == F[i]) cout << i << '\n';
    }
    cout << "end\n";
  }
}
} // namespace hellolin

// fk C++98
