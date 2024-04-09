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
static constexpr int N = 2e5 + 5, M = 4e5 + 5;
static constexpr double eps = 1e-9;
int n, m, pos, id[M], mp[N];
bool sg[N];
int64 ans;
template <class T>
T squ(T x) { return x * x; }
struct circle {
  int x, y, r;
  // bool operator<(const circle &t) const {
  //   int a = dir ? x - r : x + r, b = t.dir ? t.x - t.r : t.x + t.r;
  //   return a < b;
  // }
} c[M];
struct scircle {
  int x, y, r;
  int id;
  bool dir;
  bool operator<(const scircle &t) const {
    double a = y, b = t.y;
    if (abs(pos - x) != r) a += (dir ? 1.0 : -1.0) * sqrt(pow(r, 2) - pow(pos - x, 2));
    if (abs(pos - t.x) != t.r) b += (t.dir ? 1.0 : -1.0) * sqrt(pow(t.r, 2) - pow(pos - t.x, 2));
    if (dir) a += eps;
    if (t.dir) b += eps;
    return a < b;
  }
};
set<scircle> st;
void main() {
  io.input(n);
  for (int i = 1, x, y, r; i <= n; ++i) {
    io.input(x, y, r);
    // c[++m] = {x, y, r, true};
    // id[m] = m;
    // c[++m] = {x, y, r, false};
    // id[m] = m;
    c[i] = {x, y, r};
    id[++m] = i, id[++m] = -i;
  }
  // sort(&id[1], &id[m + 1], [&](const int &x, const int &y) { return c[x] < c[y]; });
  sort(&id[1], &id[m + 1], [&](const int &x, const int &y) {
    int a = x > 0 ? c[x].x - c[x].r : c[-x].x + c[-x].r;
    int b = y > 0 ? c[y].x - c[y].r : c[-y].x + c[-y].r;
    return a < b;
  });
  for (int i = 1; i <= m; ++i) {
    bool _ = id[i] > 0;
    int p = abs(id[i]);
    const auto &[x, y, r] = c[p];
    pos = _ ? x - r : x + r;
    scircle a = {x, y, r, p, true}, b = {x, y, r, p, false};
    if (_) {
      auto tmp = st.lower_bound(a);
      if (tmp != st.end())
        mp[p] = tmp->dir ? tmp->id : mp[tmp->id];
      st.insert(a);
      st.insert(b);
      sg[p] = !sg[mp[p]];
      ans += (sg[p] ? 1ll : -1ll) * squ((int64) r);
    } else {
      st.erase(a);
      st.erase(b);
    }
  }
  io.write(ans);
}
} // namespace hellolin