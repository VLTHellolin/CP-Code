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
constexpr static int N = 2e3 + 11;
constexpr static ll Mod = 1e9 + 7;
ll dp[N][N];
std::string l, r;
ll n, m, d;
std::vector<int> di;
ll dfs(int now, ll res, bool msk) {
    if(now<0) return !res;
    ll &ndp = dp[now][res], ans = 0;
    if(~ndp && !msk) return ndp;
    rep(int, i, 0, msk ? di[now] : 9) {
        if((n - now) & 1) {
            if(i == d)
                // break;
                continue;
        } else if(i != d)
            continue;
        ll nxt = dfs(now - 1, (res * 10 + i) % m, msk && i == di[now]);
        (ans += nxt) %= Mod;
    }
    return !msk ? ndp = ans : ans;
}
ll get_ans(std::string x) {
    std::reverse(allof(x));
    di.clear();
    for(char i : x) {
        di.pb(i - '0');
    }
    return dfs((n = di.size()) - 1, 0, 1);
}
bool cross(std::string x) {
    ll ans = 0;
    rep(int, i, 0, (int)x.size() - 1) {
        x[i] -= '0';
        if((i + 1) & 1) {
            if(x[i] == d)
                return 0;
        } else if(x[i] != d)
            return 0;
        (ans = ans * 10 + x[i]) %= m;
    }
    return !ans;
}
void solve() {
    memset(dp, -1, sizeof(dp));
    std::cin >> m >> d >> l >> r;
    std::cout << (get_ans(r) - get_ans(l) + cross(l) + Mod) % Mod << nl;
}
} // namespace hellolin