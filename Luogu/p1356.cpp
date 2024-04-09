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
constexpr static int N = 2e4 + 111;
int T, n, m;
int a[N], w;
int dp[N * 20][2];
void solve() {
    for(std::cin >> T; T--; [&]() {
        std::cin >> n >> m;

        memset(dp, 0, sizeof(dp));
        std::cin >> w;
        w = (w % m + m) % m;
        dp[w][0] = 1;
        rep(int, i, 2, n) {
            std::cin >> a[i];
            a[i] = (a[i] % m + m) % m;
            rep(int, x, 0, m-1) {
                if(dp[x][0] == i-1) {
                    dp[((x+a[i])%m+m)%m][1] = dp[((x-a[i])%m+m)%m][1] = i;
                }   
            }
            rep(int, x, 0, m-1) dp[x][0] = dp[x][1];
            // (sum += a[i]) %= m;
        }
        // dp[sum] = 1;
        // rep(int, x, 0, m-1) {
        //     per(int, i, n, 1) {
        //         if(dp[x]) {
        //             dp[((x + 2 * a[i]) % m + m) % m] = 1;
        //         }
        //     }
        // }
        std::cout << (dp[0][0] == n ? "D" : "Not d") << "ivisible\n";
    }());
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