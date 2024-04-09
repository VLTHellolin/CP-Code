// * HELLOLIN'S CP CODE TEMPLATE v2.5.0
#include <locale>
#ifndef ONLINE_JUDGE
#pragma GCC optimize(2, "inline", "unroll-loops", "no-stack-protector", "-ffast-math")
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
const static std::string yesno_str[2][3] = {{"no", "No", "NO"}, {"yes", "Yes", "YES"}};
inline std::string yesno(bool x, int y) { return yesno_str[x][y] + '\n'; }
template <class T> inline T fpow(T x, ull y) { T res = 1; for(; y; y >>= 1, x = x * x) if(y & 1) res = res * x; return res; }
template <class T> inline T fpow(T x, ull y, T mod) { T res = 1; for(; y; y >>= 1, x = x * x % mod) if(y & 1) res = res * x % mod; return res; }
template <class T, class U> inline bool chmax(T &x, U y) { return y > x ? (x = y, 1) : 0; }
template <class T, class U> inline bool chmin(T &x, U y) { return y < x ? (x = y, 1) : 0; }
#define rep(l, x, a, b) for (l x = a, x##END = b; x <= x##END; ++x)
#define per(l, x, a, b) for (l x = a, x##END = b; x >= x##END; --x)
#define fi first
#define se second
#define allof(x) x.begin(), x.end()
#define alof(x) x.begin() + 1, x.end()
#define allnof(x, n) x.begin(), x.begin() + n + 1
#define alnof(x, n) x.begin() + 1, x.begin() + n + 2
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb emplace_back
#define nl '\n'
} // namespace lib
using namespace lib;

// * CORE CODE BEGIN * //
constexpr static int N = 1e5 + 11, W = 80, P = (1 << 19) + 5;
constexpr static ll Mod = 1e9 + 7;
int n, k[W], tp;
ll w[2][W], dp[2][P];
std::vector<int> pri {-1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};
void solve() {
    rep(int, i, 0, 70)
        w[0][i] = 1;
    rep(int, i, 1, 19) {
        rep(int, j, 1, 70) {
            int q = j;
            while(q % pri[i] == 0) {
                k[j] ^= (1 << (i - 1));
                q /= pri[i];
            }
        }
    }
    std::cin >> n;
    dp[0][0] = 1;
    rep(int, i, 1, n) {
        std::cin >> tp;
        w[0][tp] = w[1][tp] = (w[0][tp] + w[1][tp]) % Mod;
    }
    rep(int, i, 0, 70) {
        int c1 = i & 1, c2 = (i+1) & 1;
        rep(int, j, 0, 1<<19) {
            dp[c2][j] = (dp[c2][j] + w[0][i] * dp[c1][j]) % Mod;
            dp[c2][k[i] ^ j] = (dp[c2][k[i] ^ j] + w[1][i] * dp[c1][j]) % Mod;
        }
        rep(int, j, 0, 1<<19)
            dp[c1][j] = 0;
    }
    if(!dp[1][0]) dp[1][0] = Mod;
    std::cout << (dp[1][0] - 1) % Mod << nl;
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