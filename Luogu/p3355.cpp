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

#ifndef HELLOLIN_GRAPH_MAX_FLOW_HPP
#define HELLOLIN_GRAPH_MAX_FLOW_HPP 1
#include <algorithm>
#include <limits>
#include <queue>
#include <vector>

namespace hellolin {

namespace graph {

template <class T>
class max_flow {
private:
    int n, m;
    std::vector<std::pair<int, int>> pr;
    class internal_edge {
    public:
        int to, p;
        T w;
    };
    std::vector<std::vector<internal_edge>> g;
    std::vector<bool> vis;
    std::queue<int> q;
    std::vector<int> s_l, s_t;

    void _bfs(int fr, int to) {
        std::fill(s_l.begin(), s_l.end(), -1);
        q = std::queue<int>();
        q.push(fr);
        s_l[fr] = 0;
        while (q.size()) {
            int tp = q.front();
            q.pop();
            for (internal_edge i : g[tp]) {
                if (i.w && s_l[i.to] < 0) {
                    s_l[i.to] = s_l[tp] + 1;
                    if (i.to == to) return;
                    q.push(i.to);
                }
            }
        }
    }
    T _dfs(int tar, int now, T p) {
        if (now == tar) return p;
        T res = 0;
        int sn = s_l[now];
        for (int &i = s_t[now]; i < (int) g[now].size(); i++) {
            internal_edge &e1 = g[now][i];
            internal_edge &e2 = g[e1.to][e1.p];
            if (sn > s_l[e1.to] && e2.w) {
                T qwq = _dfs(tar, e1.to, std::min(p - res, e2.w));
                if (qwq <= 0) continue;
                e1.w += qwq;
                e2.w -= qwq;
                res += qwq;
                if (res == p) return res;
            }
        }
        s_l[now] = n;
        return res;
    }

public:
    class edge {
        int fr, to;
        T w, flow;
    };
    explicit max_flow(int _n)
        : n(_n) {
        g.resize(n + 1);
        vis.resize(n + 1);
    }
    void add_edge(int fr, int to, T w) {
        m = pr.size();
        int _fr = g[fr].size(), _to = g[to].size();
        if (fr == to) ++_to;
        pr.push_back({fr, _fr});
        g[fr].push_back(internal_edge{to, _to, w});
        g[to].push_back(internal_edge{fr, _fr, 0});
    }
    edge get_edge(int x) {
        m = pr.size();
        internal_edge e1, e2;
        e1 = g[pr[x].first][pr[x].second];
        e2 = g[e1.to][e1.p];
        return edge{pr[x].first, e1.to, e1.w + e2.w, e2.w};
    }
    std::vector<edge> get_edges() {
        m = pr.size();
        std::vector<edge> e;
        for (int i = 0; i < m; i++) {
            e.push_back(get_edge(i));
        }
        return e;
    }
    void modify_edge(int x, T _w, T _flow) {
        m = pr.size();
        internal_edge &e1 = g[pr[x].first][pr[x].second];
        internal_edge &e2 = g[e1.to][e1.p];
        e1.w = _w - _flow;
        e2.w = _flow;
    }
    T get_flow(int fr, int to, T lim = std::numeric_limits<T>::max()) {
        T res = 0;
        s_l.resize(n + 1);
        s_t.resize(n + 1);
        while (res < lim) {
            _bfs(fr, to);
            std::fill(s_t.begin(), s_t.end(), 0);
            if (s_l[to] == -1) return res;
            T qwq = _dfs(fr, to, lim - res);
            if (!qwq) return res;
            res += qwq;
        }
        return res;
    }
    std::vector<bool> min_cut(int x) {
        vis.resize(n + 1, 0);
        q = std::queue<int>();
        q.push(x);
        while (q.size()) {
            int tp = q.front();
            q.pop();
            if (vis[tp]) continue;
            vis[tp] = 1;
            for (internal_edge i : g[tp]) {
                if (i.w && !vis[i.to]) {
                    q.push(i.to);
                }
            }
        }
        return vis;
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
constexpr static int N = 300, X = 5e4, INF = 8e8;
int n, m, s, t, x, y;
bool vis[N][N];
int dx[9] = {-1, 1, 1, 2, 2, -1, -1, -2, -2};
int dy[9] = {-1, 2, -2, 1, -1, 2, -2, 1, -1};
graph::max_flow<int> mf(X);
void solve() {
    auto calc = [&](int x, int y) {
        return n * (x - 1) + y;
    };
    std::cin >> n >> m;
    s = 0, t = n * n + 1;
    rep(int, i, 1, m) {
        std::cin >> x >> y;
        vis[x][y] = 1;
    }
    rep(int, i, 1, n)
        rep(int, j, 1, n)
            if(!vis[i][j]) {
                if((i + j) & 1) {
                    mf.add_edge(s, calc(i, j), 1);
                    rep(int, k, 1, 8) {
                        int a = i + dx[k], b = j + dy[k];
                        if(!vis[a][b])
                            if(a >= 1 && a <= n && b >= 1 && b <= n) {
                                mf.add_edge(calc(i, j), calc(a, b), INF);
                            }
                    }
                } else {
                    mf.add_edge(calc(i, j), t, 1);
                }
            }
    std::cout << n * n - m - mf.get_flow(s, t) << nl;
}
} // namespace hellolin