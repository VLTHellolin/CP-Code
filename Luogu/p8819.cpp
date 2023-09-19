// * HELLOLIN'S CP CODE TEMPLATE v3.0.1     * //
// * https://github.com/hellolin-oi/CP-Code * //
#include <numeric>
#ifndef ONLINE_JUDGE
#pragma warning(disable: 4018)
#pragma warning(disable: 4068)
#pragma warning(disable: 4800)
#pragma GCC optimize(2, "inline", "unroll-loops", "no-stack-protector", "-ffast-math")
#pragma GCC target("avx2,lzcnt,popcnt")
#endif
#include <bits/stdc++.h>
// #include "atcoder/all"

#ifndef HELLOLIN_RANDOM_NUMBER_HPP
#define HELLOLIN_RANDOM_NUMBER_HPP 1
#include <chrono>
#include <functional>
#include <random>

namespace hellolin {

class random_number {
private:
    std::mt19937_64 *gen;
    std::uniform_int_distribution<unsigned long long> dist;
    std::hash<unsigned long long> hs;
    unsigned long long get_time() {
        return std::chrono::steady_clock::now().time_since_epoch().count();
    }

public:
    explicit random_number(unsigned long long sd = 4731636727ll) {
        static std::mt19937_64 r(sd ^ get_time());
        gen = &r;
    }
    unsigned long long operator()() {
        return hs(1ll * (dist(*gen) ^ get_time()));
    }
    unsigned long long operator()(unsigned long long l, unsigned long long r) {
        return operator()() % r + l;
    }
};

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

constexpr static int N = 5e5;
int n, m, q, op;
int a[N], u, v;
int sum, ans, zc[N], sz[N];
std::vector<std::vector<int>> g;
random_number rnd;
void solve() {
    std::cin >> n >> m;
    rep(int, i, 1, n) a[i] = rnd(1, 1e8);
    sum = std::accumulate(a+1, a+1+n, 0);
    g.resize(n+1);
    rep(int, i, 1, m) {
        std::cin >> u >> v;
        ans += a[u];
        g[u].pb(v);
        sz[v] = (zc[v] += a[u]);
    }
    std::cin >> q;
    rep(int, i, 1, q) {
        std::cin >> op >> u;
        if(op & 1) std::cin >> v;
        if(op == 1) {
            ans -= a[u];
            zc[v] -= a[u];
        } else if(op == 3) {
            ans += a[u];
            zc[v] += a[u];
        } else if(op == 2) {
            ans -= zc[u];
            zc[u] = 0;
        } else {
            ans -= zc[u];
            ans += (zc[u] = sz[u]);
        }
        YESNO(ans == sum);
    }
}
} // namespace hellolin