// Hellolin v4.8.2

// clang-format off
#include <bits/stdc++.h>
#ifdef LOCAL
#include "hellolin/all/debug_tools.hpp"
#endif
using namespace std;
namespace hellolin {
using int64 = long long; using uint64 = unsigned long long; using real32 = double; using real64 = long double;
using comp = complex<real32>; template <class T> using spair = pair<T, T>;
#define cTr const T&
template <class T> bool chmax(T &x, cTr y) { return y > x ? x = y, 1 : 0; }
template <class T> bool chmin(T &x, cTr y) { return y < x ? x = y, 1 : 0; }
template <class T> bool range(cTr l, cTr r, cTr x) { return l <= x && x <= r; }
template <class T> bool range(cTr l, cTr r, cTr x, cTr y) { return l <= x && x <= y && y <= r; }
#undef cTr
class IO {
private:
  static constexpr int Buffer = 1<<19; char ib[Buffer], ob[Buffer], *is, *it, *os = ob, *ot = ob + Buffer - 1; FILE *inf, *ouf; vector<string> dt;
  void fl() { fwrite(ob, 1, os - ob, ouf), os = ob; } void pc(char x) { ((*os++ = x, os) == ot) ? fl() : void(); }
  char gc() { return is == it && ((it = (is = ib) + fread(ib, 1, Buffer, inf)), is == it) ? EOF : *is++; }
  template <class T> void up(T x) { dt.push_back(to_string(x)); } template <class T, class...A> void up(T x, A...a) { up(x), up(a...); }
public:
  void flush() { fl(), fflush(ouf); } IO(FILE *_i = stdin, FILE *_o = stdout) : inf(_i), ouf(_o) {} ~IO() { flush(); }
  void reopen(FILE *_i = stdin, FILE *_o = stdout) { flush(); inf = _i, ouf = _o; }
  void reopen(const char *i, const char *o) { FILE *_i = fopen(i, "r"), *_o = fopen(o, "w"); reopen(_i, _o); }
  template <class T> void input(T &x) {
    x = 0; bool f = 0; char c = gc(); while (!isdigit(c)) f ^= c == '-', c = gc(); while (isdigit(c)) x = x * 10 + c - 48, c = gc(); x = f ? -x : x;
  }
  void input(char &x) { do { x = gc(); } while (!isgraph(x)); } void input(char *x) { char c = gc(); while (isgraph(c)) *x++ = c, c = gc(); *x++ = '\0'; }
  void input(string &x) { char c = gc(); x = ""; while (isgraph(c)) x += c, c = gc(); }
  template <class T, class...A> void input(T &x, A &...a) { input(x), input(a...); } template <class T1, class T2> void input(pair<T1, T2> &x) { input(x.first, x.second); }
  template <class T> void write(T x) { if (x < 0) pc('-'), x = -x; if (x > 9) write(x / 10); pc(x % 10 + 48); }
  void write(char x) { pc(x); } void write(const char *x) { size_t l = strlen(x); for (size_t i = 0; i < l; ++i) pc(x[i]); }
  void write(const string &x) { for(const char &i : x) pc(i); } template <class T, class...A> void write(T x, A...a) { write(x), write(a...); }
  template <class...A> void print(const string &x, A...a) {
    dt.clear(); up(a...); string r = ""; int tp = 0; for (size_t i = 0; i < x.size(); ++i) if (x[i] == '%') r += dt[tp++]; else r += x[i]; write(r);
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
static constexpr int N = 1e5 + 5;
static constexpr int64 P = 998244353;
// template <class T, T P>
// class modint {
// private:
//   T smod(const T &a) const { return (a % P + P) % P; }

// public:
//   T x;
//   modint(T _x = 0) { x = smod(_x); }
//   template <class T2>
//   operator T2() { return T2(x); }
//   modint operator+(const modint &y) const { return smod(x + y.x); }
//   modint operator-(const modint &y) const { return smod(x - y.x); }
//   modint operator*(const modint &y) const { return smod(x * y.x); }
//   modint &operator+=(const modint &y) { return *this = *this + y; }
//   modint &operator-=(const modint &y) { return *this = *this - y; }
//   modint &operator*=(const modint &y) { return *this = *this * y; }
//   bool operator==(const modint &y) const { return x == y.x; }
// };
// using mint = modint<int, P>;
// using mint64 = modint<int64, P>;
template <class T>
class matrix2 {
public:
  T x[2][2] = {{0, 0}, {0, 0}};
  matrix2() {}
  explicit matrix2(T a, T b, T c, T d) {
    x[0][0] = a, x[0][1] = b, x[1][0] = c, x[1][1] = d;
  }
  bool operator==(const matrix2 &y) const {
    for (int i = 0; i < 2; ++i)
      for (int j = 0; j < 2; ++j)
        if (x[i][j] != y.x[i][j]) return false;
    return true;
  }
  matrix2 operator*(const matrix2 &y) const {
    matrix2 res{0, 0, 0, 0};
    for (int i = 0; i < 2; ++i)
      for (int j = 0; j < 2; ++j)
        for (int k = 0; k < 2; ++k)
          (((res.x[i][k] += ((int64) x[i][j] * y.x[j][k]) % P) %= P) += P) %= P;
    return res;
  }
  matrix2 &operator*=(const matrix2 &y) { return *this = *this * y; }
};
using mtr = matrix2<int>;
mtr O{0, 0, 0, 0}, I{1, 0, 0, 1}, E{2, 1, -1, 0}, W{1, 0, 1, 1}, B;
mtr rv(const mtr &x) { return x == I ? I : (x == E ? W : E); }
class splay_tree {
public:
  int rt = 0;

private:
  struct node {
    int anc = 0, son[2] = {0, 0}, siz = 0;
    bool tag = false, rev = false;
    mtr res[2] = {O, O}, sum[4] = {O, O, O, O};
    // node() {}
    // node(const mtr &x) {
    //   siz = 1;
    //   res[0] = sum[0] = sum[2] = x;
    //   res[1] = sum[1] = sum[3] = rv(x);
    // }
  } tr[N << 1];
  int tot = 0;
  void create_node(int &z, const mtr &x) {
    tr[z = ++tot].siz = 1;
    tr[z].res[0] = tr[z].sum[0] = tr[z].sum[2] = x;
    tr[z].res[1] = tr[z].sum[1] = tr[z].sum[3] = rv(x);
  }
  void create_tag(int x, bool flag) {
    if (!x) return;
    if (flag) {
      swap(tr[x].son[0], tr[x].son[1]);
      swap(tr[x].sum[0], tr[x].sum[2]);
      swap(tr[x].sum[1], tr[x].sum[3]);
      tr[x].rev ^= 1;
    } else {
      swap(tr[x].res[0], tr[x].res[1]);
      swap(tr[x].sum[0], tr[x].sum[1]);
      swap(tr[x].sum[2], tr[x].sum[3]);
      tr[x].tag ^= 1;
    }
  }
  bool check(int x, int f) { return tr[f].son[1] == x; }
  void join(int x, int f, bool p) { tr[x].anc = f, tr[f].son[p] = x; }
  void pushup(int x) {
    node &rt = tr[x];
    const node &ls = tr[tr[x].son[0]], &rs = tr[tr[x].son[1]];
    rt.siz = ls.siz + rs.siz + 1;
    rt.sum[0] = ls.sum[0] * rt.res[0] * rs.sum[0];
    rt.sum[1] = ls.sum[1] * rt.res[1] * rs.sum[1];
    rt.sum[2] = rs.sum[2] * rt.res[0] * ls.sum[2];
    rt.sum[3] = rs.sum[3] * rt.res[1] * ls.sum[3];
  }
  void pushdown(int x) {
    if (tr[x].tag) {
      create_tag(tr[x].son[0], false);
      create_tag(tr[x].son[1], false);
      tr[x].tag = false;
    }
    if (tr[x].rev) {
      create_tag(tr[x].son[0], true);
      create_tag(tr[x].son[1], true);
      tr[x].rev = false;
    }
  }
  void rotate(int x) {
    int f = tr[x].anc, F = tr[f].anc;
    // bool flag = check(x, f), flag2 = check(f, F);
    bool flag = check(x, f);
    join(tr[x].son[!flag], f, flag);
    bool flag2 = check(f, F);
    join(x, F, flag2);
    join(f, x, !flag);
    pushup(f);
    pushup(x);
  }
  void splay(int x, int y) {
    if (!y) rt = x;
    while (tr[x].anc != y) {
      int f = tr[x].anc, F = tr[f].anc;
      if (F != y) {
        rotate(check(x, f) ^ check(f, F) ? x : f);
      }
      rotate(x);
    }
  }
  int query(int p) {
    int x = rt;
    while (x) {
      pushdown(x);
      if (p == tr[tr[x].son[0]].siz + 1) {
        splay(x, 0);
        break;
      }
      if (p <= tr[tr[x].son[0]].siz)
        x = tr[x].son[0];
      else
        p -= tr[tr[x].son[0]].siz + 1, x = tr[x].son[1];
    }
    return x;
  }
  void split(int l, int r) {
    int x = query(l), y = query(r + 2);
    splay(x, 0), splay(y, x);
  }

public:
  splay_tree() {
    tr[0].res[0] = tr[0].res[1] = I;
    for (int i = 0; i < 4; ++i)
      tr[0].sum[i] = I;
  }
  const mtr &GET() { return tr[rt].sum[0]; }
  void build(const char *s, int l, int r, int &x, int f, bool flag) {
    int mid = (l + r) >> 1;
    create_node(x, s[mid] == 'W' ? W : (s[mid] == 'E' ? E : I));
    join(x, f, flag);
    if (l < mid) build(s, l, mid - 1, tr[x].son[0], x, false);
    if (r > mid) build(s, mid + 1, r, tr[x].son[1], x, true);
    pushup(x);
  }
  void insert(int x, const mtr &m) {
    split(x + 1, x);
    int P;
    create_node(P, m);
    join(P, tr[rt].son[1], false);
    pushup(tr[rt].son[1]);
    pushup(rt);
  }
  void update(int l, int r, bool p) {
    split(l, r);
    create_tag(tr[tr[rt].son[1]].son[0], p);
    pushup(tr[rt].son[1]);
    pushup(rt);
  }
};
int n, q;
char s[N];
splay_tree shiroko;
void main() {
  // io.input(n, q);
  cin >> n >> q;
  s[0] = s[n + 1] = 'I';
  for (int i = 1; i <= n; ++i)
    // io.input(s[i]);
    cin >> s[i];
  B = mtr(0, 1, 1, 0) * mtr(1, 1, 1, 0);
  shiroko.build(s, 0, n + 1, shiroko.rt, 0, false);
  mtr ans = B * shiroko.GET();
  io.print("% %\n", ans.x[0][0], ans.x[1][0]);
  // for (int _ = 0; _ < 2; ++_)
  //   for (int __ = 0; __ < 2; ++__)
  //     cerr << B.x[_][__] << ' ';
  // cerr << endl;
  for (int i = 1, l, r; i <= q; ++i) {
    string op;
    char x;
    // io.input(op);
    cin >> op;
    if (op == "APPEND") {
      // io.input(x);
      cin >> x;
      shiroko.insert(n++, x == 'W' ? W : E);
    } else if (op == "FLIP") {
      // io.input(l, r);
      cin >> l >> r;
      shiroko.update(l, r, false);
    } else if (op == "REVERSE") {
      // io.input(l, r);
      cin >> l >> r;
      shiroko.update(l, r, true);
    }
    ans = B * shiroko.GET();
    // for (int _ = 0; _ < 2; ++_)
    //   for (int __ = 0; __ < 2; ++__)
    //     cerr << shiroko.GET().x[_][__] << ' ';
    // cerr << endl;
    io.print("% %\n", ans.x[0][0], ans.x[1][0]);
  }
}
} // namespace hellolin
