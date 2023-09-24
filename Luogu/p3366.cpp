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

#ifndef HELLOLIN_DS_DSU_HPP
#define HELLOLIN_DS_DSU_HPP 1
#include <algorithm>
#include <vector>

namespace hellolin {

namespace ds {

class dsu {
private:
    int n;
    std::vector<int> g;

public:
    explicit dsu(int _n)
        : n(_n) {
        g.resize(n + 1, -1);
    }

    int find(int x) {
        return g[x] < 0 ? x : g[x] = find(g[x]);
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    int size(int x) {
        return -g[find(x)];
    }
    int merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return x;
        if (-g[x] < -g[y]) std::swap(x, y);
        g[x] += g[y];
        g[y] = x;
        return x;
    }
    void erase(int x) {
        ++g[find(x)];
        g[x] = -1;
    }
    void swap(int x, int y) {
        int _x = x;
        x = find(x), y = find(y);
        if(x==y) return;
        g[_x] = y;
        ++g[x], --g[y];
    }
};

} // namespace ds

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
constexpr static int N = 5555, M = 2e5 + 11;
class edge {
public:
    int u, v, w;
    bool operator<(const edge& e) const {
        return w < e.w;
    }
} e[M];
int n, m, ans, all;
ds::dsu d(N);
void solve() {
    std::cin >> n >> m;
    if(m < n - 1) {
        std::cout << "orz\n";
        return;
    }
    rep(int, i, 1, m) {
        std::cin >> e[i].u >> e[i].v >> e[i].w;
    }
    std::sort(e+1, e+1+m);
    rep(int, i, 1, m) {
        if(!d.same(e[i].u, e[i].v)) {
            ++all;
            d.merge(e[i].u, e[i].v);
            ans += e[i].w;
        }
    }
    if(all != n - 1) std::cout << "orz\n";
    else std::cout << ans << nl;
}
} // namespace hellolin