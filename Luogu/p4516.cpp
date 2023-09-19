// * HELLOLIN'S CP CODE TEMPLATE v2.5.0
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
constexpr static int N = 1e5 + 2, K = 1e2 + 2;
constexpr static ll Mod = 1e9 + 7;
int n, k;
int u, v;
int dp[N][K][2][2], ec[N], mec;
int jt[K][2][2];
std::vector<std::vector<int>> g;
void solve() {
    auto dfs = [&](auto fun, int x, int fa) -> void {
        ec[x] = 1;
        dp[x][0][0][0] = dp[x][1][1][0] = 1;
        for(auto y : g[x]) {
            if(y != fa) {
                fun(fun, y, x);
                
                mec = std::min(k, ec[x] + ec[y]);
                rep(int, i, 0, ec[x]) {
                    rep(int, j, 0, ec[y]) {
                        if(i + j > mec) break;
                        rep(int, a, 0, 1) rep(int, b, 0, 1) rep(int, c, 0, 1) rep(int, d, 0, 1) if(a | d) {
                            jt[i + j][a][b | c] = (jt[i + j][a][b | c] + 1ll * dp[x][i][a][b] * dp[y][j][c][d] % Mod) % Mod;
                        }
                    }
                }
                ec[x] = mec;
                rep(int, a, 0, mec)
                    rep(int, i, 0, 1) {
                        rep(int, j, 0, 1) {
                            dp[x][a][i][j] = jt[a][i][j];
                            jt[a][i][j] = 0;
                        }
                    }
            }
        }
        
        
    };
    std::cin >> n >> k;
    g.resize(n + 1);
    rep(int, i, 1, n - 1) {
        std::cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    dfs(dfs, 1, 0);
    std::cout << (dp[1][k][0][1] + dp[1][k][1][1]) % Mod << nl;

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