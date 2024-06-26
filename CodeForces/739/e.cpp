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


#ifndef HELLOLIN_GRAPH_MAX_COST_FLOW_HPP
#define HELLOLIN_GRAPH_MAX_COST_FLOW_HPP 1
#include <algorithm>
#include <limits>
#include <queue>
#include <vector>

namespace hellolin {

namespace graph {
static constexpr long double eps = 1e-9;

template <class T, class H>
class max_cost_flow {
private:
  int n, m;
  long long inf;
  std::vector<std::pair<int, int>> pr;
  class internal_edge {
  public:
    int to, p;
    T w;
    H cost;
  };
  std::vector<std::vector<internal_edge>> g;
  std::vector<bool> vis;
  class spfa_node {
  public:
    T flow;
    H dis;
    std::pair<int, int> p;
  };
  std::vector<spfa_node> s;
  T flow_res;
  H cost_res;
  std::queue<int> q;

  bool spfa(int fr, int to) {
    for (int i = 1; i <= n; i++) {
      s[i].dis = -inf;
    }
    vis.clear();
    vis[fr] = 1;
    q = std::queue<int>();
    q.push(fr);
    s[fr].dis = 0;
    s[fr].flow = inf;
    while (q.size()) {
      int tp = q.front();
      q.pop();
      vis[tp] = 0;
      int ind = -1;
      for (internal_edge &i : g[tp]) {
        ++ind;
        if (i.w > 0 && i.cost + s[tp].dis > s[i.to].dis + eps) {
          s[i.to].dis = i.cost + s[tp].dis;
          s[i.to].flow = std::min(s[tp].flow, i.w);
          s[i.to].p = {tp, ind};
          if (!vis[i.to]) {
            vis[i.to] = 1;
            q.push(i.to);
          }
        }
      }
    }
    return s[to].dis != -inf;
  }
  void _upd(int fr, int to) {
    int tp1 = to, tp2 = -1, tp3 = -1;
    while (tp1 != fr) {
      tp2 = s[tp1].p.first;
      tp3 = s[tp1].p.second;
      g[tp2][tp3].w -= s[to].flow;
      g[tp1][g[tp2][tp3].p].w += s[to].flow;
      tp1 = tp2;
    }
    flow_res += s[to].flow;
    cost_res += s[to].flow * s[to].dis;
  }

public:
  class edge {
  public:
    int fr, to;
    T w, flow;
    H cost;
  };
  explicit max_cost_flow(int _n, long long _inf = 1e9)
      : n(_n)
      , inf(_inf) {
    g.resize(n + 1);
    vis.resize(n + 1);
    s.resize(n + 1);
  }
  void add_edge(int fr, int to, T w, H co) {
    m = pr.size();
    int _fr = g[fr].size(), _to = g[to].size();
    if (fr == to) ++_to;
    pr.push_back({fr, _fr});
    g[fr].push_back(internal_edge{to, _to, w, co});
    g[to].push_back(internal_edge{fr, _fr, 0, -co});
  }
  edge get_edge(int x) {
    m = pr.size();
    internal_edge e1, e2;
    e1 = g[pr[x].first][pr[x].second];
    e2 = g[e1.to][e1.p];
    return edge{pr[x].first, e1.to, e1.w + e2.w, e2.w, e1.cost + e2.cost};
  }
  std::vector<edge> get_edges() {
    m = pr.size();
    std::vector<edge> e;
    for (int i = 0; i < m; i++) {
      e.push_back(get_edge(i));
    }
    return e;
  }
  std::pair<T, H> get_flow_cost(int fr, int to, T flow_lim = std::numeric_limits<T>::max(), H cost_lim = std::numeric_limits<H>::max()) {
    flow_res = cost_res = 0;
    while (spfa(fr, to) && flow_res < flow_lim && cost_res < cost_lim)
      _upd(fr, to);
    return {flow_res, cost_res};
  }
};

} // namespace graph

} // namespace hellolin

#endif

namespace hellolin {
static constexpr int N = 2050;
int n, a, b, s, t, x, y;
long double p[N], q[N];
void main() {
  // io.input(n, a, b);
  scanf("%d%d%d", &n, &a, &b);
  graph::max_cost_flow<int, long double> mcf(n + 5);
  s = 0, t = n + 1, x = t + 1, y = t + 2;
  for (int i = 1; i <= n; ++i)
    scanf("%Lf", &p[i]);
  for (int i = 1; i <= n; ++i)
    scanf("%Lf", &q[i]);
  mcf.add_edge(s, x, a, 0);
  mcf.add_edge(s, y, b, 0);
  for (int i = 1; i <= n; ++i) {
    mcf.add_edge(x, i, 1, p[i]);
    mcf.add_edge(y, i, 1, q[i]);
    mcf.add_edge(i, t, 1, 0);
    mcf.add_edge(i, t, 1, -(p[i] * q[i]));
  }
  printf("%.5Lf\n", mcf.get_flow_cost(s, t).second);
}
} // namespace hellolin