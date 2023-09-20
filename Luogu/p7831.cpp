/*
██╗  ██╗███████╗██╗     ██╗      ██████╗ ██╗     ██╗███╗   ██╗
██║  ██║██╔════╝██║     ██║     ██╔═══██╗██║     ██║████╗  ██║
███████║█████╗  ██║     ██║     ██║   ██║██║     ██║██╔██╗ ██║
██╔══██║██╔══╝  ██║     ██║     ██║   ██║██║     ██║██║╚██╗██║
██║  ██║███████╗███████╗███████╗╚██████╔╝███████╗██║██║ ╚████║
╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ ╚═════╝ ╚══════╝╚═╝╚═╝  ╚═══╝ 's CP Code Template!
Version 3.2.0.
Recommended standard: C++20. Minimum standard: C++17.
In general, this source code can be found archived here: https://github.com/hellolin-oi/CP-Code
The main code section is at the end of this file.
*/
#include <functional>
#ifndef ONLINE_JUDGE
#pragma warning(disable: 4018)
#pragma warning(disable: 4068)
#pragma warning(disable: 4800)
#pragma GCC optimize(2, "inline", "unroll-loops", "no-stack-protector", "-ffast-math")
#pragma GCC target("sse4,avx2,lzcnt,popcnt")
#endif
#include <bits/stdc++.h>
// #include "atcoder/all"
#ifdef LOCAL
#include "hellolin/utility/process_occupy"
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
template <class T> inline T read_next() { T res; std::cin >> res; return res; }
template <class T> inline void read_arr(T &x, int l, int r) { for(; l <= r; ++l) std::cin >> x[l]; }
inline void __debug() { std::cerr << '\n'; }
template <class T, class... Args> inline void __debug(T x, Args... y) { std::cerr << x << ' '; __debug(y...); }
#ifndef ONLINE_JUDGE
#define debug __debug
#else
#define debug if(0) __debug
#endif
#define rep(x, a, b) for (auto x = a, x##END = b; x <= x##END; ++x)
#define per(x, a, b) for (auto x = a, x##END = b; x >= x##END; --x)
#define fec(x, a) for (auto &x : a)
#define fileio(x) freopen(x".in", "r", stdin); freopen(x".out", "w", stdout)
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define allof(x) x.begin(), x.end()
#define lowbit(x) (x & -x)
#define mp make_pair
#define mt make_tuple
#define ins insert
#define ps emplace
#define pb emplace_back
#define nl '\n'
#if __cplusplus < 202202LL
#define popcount __builtin_popcountll
#endif
void solve();
} // namespace hellolin

int main() {
    // fileio("");
    // freopen(".dbg", "w", stderr);
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin.exceptions(std::cin.failbit);
    // std::cout << std::fixed << std::setprecision(6);
    std::cerr << std::fixed << std::setprecision(6);
    hellolin::solve();
#ifdef LOCAL
    std::cerr << "Memory usage: "<< hellolin::utility::get_memory_usage(hellolin::utility::get_current_pid()) << "MB.\n";
#endif
    return 0;
}

namespace hellolin {
constexpr int N = 2e5 + 14;
int n, m;
class node {
public:
    int to, nxt;
    int r, p, num;
};
std::vector<node> g(1);
int ind[N];
int head[N];
class edge {
public:
    int u, v, r, p, num;
    void add_as_edge() {
        g.push_back({u, head[v], r, p, num});
        head[v] = g.size() - 1;
        ++ind[u];
    }
    bool operator<(const edge &t) const {
        return r < t.r;
    }
    bool operator>(const edge &t) const {
        return r > t.r;
    }
    friend std::istream &operator>>(std::istream &in, edge &e) {
        in >> e.u >> e.v >> e.r >> e.p;
        return in;
    }
} ed[N];
int ans[N];
bool vis[N];
std::queue<int> q;
void topo() {
    q = decltype(q) ();
    std::fill(vis+1, vis+1+n, 0);
    std::fill(ans+1, ans+1+n, 1e9+1);
    rep(i, 1, n) if(!ind[i]) q.ps(i);
    rep(i, 1, m) {
        while(q.size()) {
            int x = q.front();
            q.pop();
            for(int i = head[x]; i; i = g[i].nxt) {
                if(vis[g[i].num]) continue;
                vis[g[i].num] = 1;
                int y = g[i].to;
                if(--ind[y] == 0) q.ps(y);
                if(ans[x] <= 1e9) chmin(ans[y], std::max((ll)g[i].r, ans[x] - (ll)g[i].p));
            }
        }
        if(!vis[ed[i].num]) {
            vis[ed[i].num] = 1;
            chmin(ans[ed[i].u], ed[i].r);
            if(--ind[ed[i].u] == 0) q.ps(ed[i].u);
        }
    }
}
void solve() {
    std::cin >> n >> m;
    rep(i, 1, m) {
        std::cin >> ed[i];
        ed[i].num = i;
        ed[i].add_as_edge();
    }
    std::sort(ed+1, ed+1+m, std::greater<edge>());
    topo();
    rep(i, 1, n)
        std::cout << (ans[i] > 1e9 ? -1 : ans[i]) << " \n"[i==n];
}
} // namespace hellolin