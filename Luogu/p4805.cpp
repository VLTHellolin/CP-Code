// * HELLOLIN'S CP CODE TEMPLATE v3.0.0     * //
// * https://github.com/hellolin-oi/CP-Code * //
#include <cmath>
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
constexpr static int N = 500;
int n;
int a[N], l, r, lx, rx;
ll dp[N][N], ans;
void solve() {
    std::cin >> n;
    rep(int, i, 1, n) {
        std::cin >> a[i];
        dp[i][i] = a[i];
    }
    rep(int, len, 2, n) {
        l = r = 0;
        l = 1;
        // while(r < n) {
        for(; r<n; ++l) {
            r = l + len - 1;
            // std::cerr << l << ' ' << r << nl;
            rep(int, i, l, r - 1) {
                if(dp[l][i] == dp[i+1][r]) {
                    if(dp[l][i]) {
                        dp[l][r] = dp[l][i] + dp[i+1][r];
                        break;
                    }
                }
            }
            if(dp[l][r]) continue;
            lx = l, rx = r;
            while(lx + 1 < rx) { // at lease 1
#define ndp dp[l][r]
#define ldp dp[l][lx]
#define rdp dp[rx][r]
#define mdp dp[lx+1][rx-1]
                while(!ldp && lx + 1 < rx) ++lx;
                while(!rdp && lx + 1 < rx) --rx;
                if(ldp < rdp) ++lx;
                else if(ldp > rdp) --rx;
                else if(!mdp) // middle
                    ++lx, --rx;
                else {
                    ndp = ldp + mdp + rdp;
                    break;
                }
#undef ndp
#undef ldp
#undef rdp
#undef mdp
            }
        }

    }
    rep(int, i, 1, n)
        rep(int, j, 1, n)
            chmax(ans, dp[i][j]);

    std::cout << ans << nl;


}
} // namespace hellolin