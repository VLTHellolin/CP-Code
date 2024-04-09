// * HELLOLIN'S CP CODE TEMPLATE v3.0.0     * //
// * https://github.com/hellolin-oi/CP-Code * //
#ifndef ONLINE_JUDGE
#pragma warning(disable: 4018)
#pragma warning(disable: 4068)
#pragma warning(disable: 4800)
#pragma GCC optimize(2, "inline", "unroll-loops", "no-stack-protector", "-ffast-math")
#pragma GCC target("avx2,lzcnt,popcnt")
#endif
#include <bits/stdc++.h>
#ifdef ATCODER
#include "atcoder/all"
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
constexpr static ll Mod = 998244353, W = 20, W2 = 1100;
std::pair<ll,ll> dp[W][W2];
ll l, r, k;
std::vector<int> d;

void clear() {
    rep(int, i, 0, W - 1)
        rep(int, j, 0, W2 - 1)
            dp[i][j] = {-1, -1};
}
std::pair<ll,ll> dfs(int now, int msk, bool zer, bool ok) {
    if(!now) return {0, popcount(msk) <= k};
    auto &ndp = dp[now][msk];
    if(~ndp.fi && ~ndp.se && !zer && !ok) return ndp;
    std::pair<ll,ll> res = {0, 0};
    rep(int, i, 0, ok ? d[now] : 9) {
        bool r0 = zer && !i;
        int num = r0 ? msk : msk | 1<<i;
        auto nxt = dfs(now-1, num, r0, ok && i == d[now]);
        (res.fi += nxt.se * fpow(10ll, now - 1, Mod) % Mod * i % Mod + nxt.fi) %= Mod;
        (res.se += nxt.se) %= Mod;
    }
    return (!zer && !ok ? ndp = res : res);
}
ll get_ans(ll x) {
    clear();
    d.clear();
    d.pb(0);
    do {
        d.pb(x % 10);
        x /= 10;
    } while(x);
    return dfs(d.size()-1, 0, 1, 1).fi;
}
void solve() {
    std::cin >> l >> r >> k;
    std::cout << (get_ans(r) - get_ans(l - 1) + Mod) % Mod;
}
} // namespace hellolin