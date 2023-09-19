// * HELLOLIN'S CP CODE TEMPLATE v2.6.0
// * https://github.com/hellolin-oi/CP-Code
#ifndef ONLINE_JUDGE
#pragma warning(disable: 4018)
#pragma warning(disable: 4068)
#pragma warning(disable: 4800)
#pragma GCC optimize(2, "inline", "unroll-loops", "no-stack-protector", "-ffast-math")
#pragma GCC target("avx2,lzcnt,popcnt")
#endif
#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>
#ifdef LOCAL
#include <windows.h>
#include <psapi.h>
#endif

namespace hellolin {
namespace lib {
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
#define rep(l, x, a, b) for (l x = a, x##END = b; x <= x##END; ++x)
#define per(l, x, a, b) for (l x = a, x##END = b; x >= x##END; --x)
#define fi first
#define se second
#define allof(x) x.begin(), x.end()
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb emplace_back
#define nl '\n'
} // namespace lib
using namespace lib;

// * CORE CODE BEGIN * //
constexpr static int N = 20, W = 114, eN = 1 << N;
int n, x, y, ts;
int a[N], sum;
int pre[eN];
bool nt[eN], vis[W][eN], dp[W][eN];
bool dfs(int now, int rs) {
        bool &ndp = dp[now][rs], &nvi = vis[now][rs];
        int rev = pre[rs] / now;
        if(nvi) return ndp;
        if(vis[rev][rs]) return dp[rev][rs];
        nvi = 1;

        if(nt[rs]) return ndp = 1;
        for(int tp = rs & (rs - 1); tp; tp = rs & (tp - 1)) {
            if((pre[tp] % now == 0 && dfs(now, tp) && dfs(now, tp ^ rs))
            || (pre[tp] % rev == 0 && dfs(rev, tp) && dfs(rev, tp ^ rs))) return ndp = 1;
        }

        return dp[now][rs];
    };
void solve() {
    // auto dfs = [&](auto fun, int now, int rs) -> bool {
    //     bool &ndp = dp[now][rs], &nvi = vis[now][rs];
    //     int rev = pre[rs] / now;
    //     if(nvi) return ndp;
    //     if(vis[rev][rs]) return dp[rev][rs];
    //     nvi = 1;

    //     if(nt[rs]) return ndp = 1;
    //     for(int tp = rs & (rs - 1); tp; tp = rs & (tp - 1)) {
    //         if((pre[tp] % now == 0 && fun(fun, now, tp) && fun(fun, now, tp ^ rs))
    //         || (pre[tp] % rev == 0 && fun(fun, rev, tp) && fun(fun, rev, tp ^ rs))) return ndp = 1;
    //     }

    //     return dp[now][rs];
    // };
    while(std::cin >> n && n) {
        std::cout << "Case " << ++ts << ": ";
        std::cin >> x >> y;
        sum = 0;
        rep(int, i, 1, n) {
            std::cin >> a[i];
            sum += a[i];
        }
        if(x * y != sum) {
            YesNo(0);
            continue;
        }
        rep(int, i, 0, 1<<n) nt[i] = pre[i] = 0;
        rep(int, i, 0, 100) rep(int, j, 0, 1<<n) vis[i][j] = dp[i][j] = 0;
        rep(int, i, 1, (1<<n) - 1)
            rep(int, j, 1, n) if(i & 1 << (j-1)) pre[i] += a[j];
        rep(int, i, 1, n) nt[1 << (i-1)] = 1;
        // YesNo(dfs(dfs, x, (1<<n) - 1));
        YesNo(dfs(x, (1<<n) - 1));
    }
}
// * CORE CODE END * //

} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    // freopen(".dbg", "w", stderr);
#ifdef LOCAL
    auto st = std::chrono::high_resolution_clock::now();
#endif
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    // std::cout << std::fixed << std::setprecision(6);
    std::cerr << std::fixed << std::setprecision(6);
    hellolin::solve();
#ifdef LOCAL
    auto ed = std::chrono::high_resolution_clock::now();
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    std::cerr << "---------- DEBUG INFO ----------\n";
    std::cerr << "Time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(ed - st).count() * 1e-9 << "s.\n";
    std::cerr << "Memory: " << pmc.WorkingSetSize / 1000000 << "MB.\n";
#endif
    return 0;
}