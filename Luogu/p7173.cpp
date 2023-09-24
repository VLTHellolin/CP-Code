// * HELLOLIN'S CP CODE TEMPLATE v3.0.1     * //
// * https://github.com/hellolin-oi/CP-Code * //
#ifndef ONLINE_JUDGE
#pragma warning(disable: 4018)
#pragma warning(disable: 4068)
#pragma warning(disable: 4800)
#pragma GCC optimize(2, "inline", "unroll-loops", "no-stack-protector", "-ffast-math")
#pragma GCC target("avx2,lzcnt,popcnt")
#endif
#include <bits/stdc++.h>
// #include "atcoder/all"

#ifndef HELLOLIN_GRAPH_MIN_COST_FLOW_HPP
#define HELLOLIN_GRAPH_MIN_COST_FLOW_HPP 1
#include <algorithm>
#include <limits>
#include <queue>
#include <vector>

namespace hellolin {

namespace graph {

template <class T, class H>
class min_cost_flow {
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
            s[i].dis = inf;
        }
        vis.clear();
        vis[fr] = 1;
        q = std::queue<int> ();
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
                if (i.w > 0 && i.cost + s[tp].dis < s[i.to].dis) {
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
        return s[to].dis != inf;
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
    explicit min_cost_flow(int _n, long long _inf = 1e9)
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
using ll = long long;
using ull = unsigned long long;
using lll = __int128;
using ulll = __uint128_t;
using ld = long double;
const static std::string yesno_str[2][3] = {{"no", "No", "NO"}, {"yes", "Yes", "YES"}};
template <int M> inline void yesno_base(bool x) { std::cout << yesno_str[x][M] << '\n'; }
#define yesno(x) yesno_base<0>(x)
#define YesNo(x) yesno_base<1>(x)
#define YESNO(x) yesno_base<2>(x)
template <class T> inline T fpow(T x, ull y) { T res = 1; for(; y; y >>= 1, x = x * x) if(y & 1) res = res * x; return res; }
template <class T> inline T fpow(T x, ull y, T mod) { T res = 1; for(; y; y >>= 1, x = x * x % mod) if(y & 1) res = res * x % mod; return res; }
template <class T, class U> inline bool chmax(T &x, U y) { return y > x ? (x = y, 1) : 0; }
template <class T, class U> inline bool chmin(T &x, U y) { return y < x ? (x = y, 1) : 0; }
inline void __debug() { std::cerr << '\n'; }
template <class T, class... Args> inline void __debug(T x, Args... y) { std::cerr << x << ' '; __debug(y...); }
#ifndef ONLINE_JUDGE
#define debug __debug
#else
#define debug if(0) __debug
#endif
#define rep(l, x, a, b) for (l x = a, x##END = b; x <= x##END; ++x)
#define per(l, x, a, b) for (l x = a, x##END = b; x >= x##END; --x)
#define fi first
#define se second
#define allof(x) x.begin(), x.end()
#define lowbit(x) (x & -x)
#define mp make_pair
#define ps emplace
#define pb emplace_back
#define nl '\n'
#if __cplusplus < 202202LL
#define popcount __builtin_popcountll
#endif
void solve();
} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    // freopen(".dbg", "w", stderr);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    // std::cout << std::fixed << std::setprecision(6);
    std::cerr << std::fixed << std::setprecision(6);
    hellolin::solve();
    return 0;
}

namespace hellolin {
constexpr static int N = 400, INF = 8e8;
int n, m, fs, ft, s, t;
int x, y, f, v;
int a1, a2, tp;
int ul[N];
graph::min_cost_flow<int, int> mcf(N);
void solve() {
    std::cin >> n >> m >> fs >> ft;
    rep(int, i, 1, m) {
        std::cin >> x >> y >> f >> v;
        if(v >= 0) {
            mcf.add_edge(x, y, f, v);
        } else {
            mcf.add_edge(y, x, f, -v);
            a2 += f * v;
            ul[y] += f;
            ul[x] -= f;
        }
    }
    s = 0, t = n + 1;
    mcf.add_edge(t, s, INF, 0);
    rep(int, i, 1, n) {
        if(ul[i]) {
            if(ul[i] > 0)
                mcf.add_edge(s, i, ul[i], 0);
            else
                mcf.add_edge(i, t, -ul[i], 0);
        }
    }
    a2 += mcf.get_flow_cost(s, t).se;
    std::tie(a1, tp) = mcf.get_flow_cost(fs, ft);

    std::cout << a1 << ' ' << a2 + tp << nl;

}
} // namespace hellolin