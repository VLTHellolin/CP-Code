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
static constexpr int N = 1e5 + 5, Inf = 1e9 + 114;
string dict[3]{"at least one", "any", "none"};
int n, m, fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) {
  x = find(x), y = find(y);
  fa[x] = y;
}
struct edge {
  int u, v, w, i;
  bool at;
  bool operator<(const edge &x) const {
    return w < x.w;
  }
} e[N];
int head[N], gtot;
int in[N];
struct graph_edge {
  int nxt, to, i;
} gra[N << 2];
void add_edge(int u, int v, int i) {
  gra[++gtot] = {head[u], v, i};
  head[u] = gtot;
}
int w[N];
short ans[N];
namespace hld {
int dfn[N], idx[N], siz[N], anc[N], son[N], top[N], deg[N];
int tmp;
void dfs1(int x = 1, int f = 0) {
  anc[x] = f;
  siz[x] = 1;
  deg[x] = deg[f] + 1;
  for (int i = head[x], y; i; i = gra[i].nxt) {
    y = gra[i].to;
    if (y == f) continue;
    in[y] = gra[i].i;
    dfs1(y, x);
    siz[x] += siz[y];
    if (siz[son[x]] < siz[y]) son[x] = y;
  }
}
void dfs2(int x = 1, int t = 1) {
  top[x] = t;
  idx[dfn[x] = ++tmp] = x;
  if (!son[x]) return;
  dfs2(son[x], t);
  for (int i = head[x], y; i; i = gra[i].nxt) {
    y = gra[i].to;
    if (y == anc[x] || y == son[x]) continue;
    dfs2(y, y);
  }
}
} // namespace hld
namespace seg_tree {
int m1[N << 2], m2[N << 2], lz[N << 2];
void pushup(int x) {
  // chmin(m1[x], min(m1[x << 1], m1[x << 1 | 1]));
  // chmax(m2[x], max(m2[x << 1], m2[x << 1 | 1]));
  m1[x] = min(m1[x << 1], m1[x << 1 | 1]);
  m2[x] = max(m2[x << 1], m2[x << 1 | 1]);
}
void pushdown(int x) {
  if (lz[x] != Inf) {
    chmin(lz[x << 1], lz[x]), chmin(m1[x << 1], lz[x]);
    chmin(lz[x << 1 | 1], lz[x]), chmin(m1[x << 1 | 1], lz[x]);
    lz[x] = Inf;
  }
}
void build_tree(int l = 1, int r = n, int x = 1) {
  lz[x] = Inf;
  if (l == r) {
    m1[x] = Inf;
    m2[x] = w[in[hld::idx[l]]];
    return;
  }
  int mid = (l + r) >> 1;
  build_tree(l, mid, x << 1);
  build_tree(mid + 1, r, x << 1 | 1);
  pushup(x);
}
void modify(int l, int r, int k, int lx = 1, int rx = n, int x = 1) {
  if (l <= lx && rx <= r) return chmin(lz[x], k), chmin(m1[x], k), void();
  pushdown(x);
  int mid = (lx + rx) >> 1;
  if (l <= mid) modify(l, r, k, lx, mid, x << 1);
  if (mid < r) modify(l, r, k, mid + 1, rx, x << 1 | 1);
  pushup(x);
}
int query(int l, int r, int lx = 1, int rx = n, int x = 1) {
  if (l <= lx && rx <= r) return m2[x];
  pushdown(x);
  int res = -Inf, mid = (lx + rx) >> 1;
  if (l <= mid) chmax(res, query(l, r, lx, mid, x << 1));
  if (mid < r) chmax(res, query(l, r, mid + 1, rx, x << 1 | 1));
  return res;
}
void check(int l = 1, int r = n, int x = 1) {
  if (l == r) {
    int u = in[hld::idx[l]];
    if (m1[x] != w[u]) ans[u] = 1;
    return;
  }
  pushdown(x);
  int mid = (l + r) >> 1;
  check(l, mid, x << 1);
  check(mid + 1, r, x << 1 | 1);
}
} // namespace seg_tree
namespace hld {
void modify(int u, int v, int x) {
  for (; top[u] != top[v]; u = anc[top[u]]) {
    if (deg[top[u]] < deg[top[v]]) swap(u, v);
    seg_tree::modify(dfn[top[u]], dfn[u], x);
  }
  if (deg[u] < deg[v]) swap(u, v);
  if (u != v) seg_tree::modify(dfn[v] + 1, dfn[u], x);
}
int query(int u, int v) {
  int res = -Inf;
  for (; top[u] != top[v]; u = anc[top[u]]) {
    if (deg[top[u]] < deg[top[v]]) swap(u, v);
    chmax(res, seg_tree::query(dfn[top[u]], dfn[u]));
  }
  if (deg[u] < deg[v]) swap(u, v);
  if (u != v) chmax(res, seg_tree::query(dfn[v] + 1, dfn[u]));
  return res;
}
} // namespace hld
void main() {
  cin >> n >> m;
  for (int i = 1, x, y, z; i <= m; ++i) {
    cin >> x >> y >> z;
    e[i] = {x, y, z, i, false};
    w[i] = z;
  }
  w[0] = Inf;
  sort(&e[1], &e[m + 1]);
  for (int i = 1; i <= n; ++i)
    fa[i] = i;
  for (int i = 1; i <= m; ++i) {
    auto &[x, y, z, p, k] = e[i];
    int fx = find(x), fy = find(y);
    if (fx == fy) continue;
    merge(fx, fy);
    k = true;
    add_edge(x, y, p);
    add_edge(y, x, p);
  }
  hld::dfs1(), hld::dfs2(), seg_tree::build_tree();
  for (int i = 1; i <= m; ++i) {
    if (e[i].at) continue;
    auto &[x, y, z, p, k] = e[i];
    if (z != hld::query(x, y)) ans[p] = 2;
    hld::modify(x, y, z);
  }
  seg_tree::check();
  for (int i = 1; i <= m; ++i)
    cout << dict[ans[i]] << '\n';
}
} // namespace hellolin