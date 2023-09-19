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
constexpr static int N = 1e4 + 11;
int n, v, w;
bool vis[N];
ll dp[N][2];
std::vector<std::vector<std::pair<int, int>>> g;
void solve() {
    auto dfs1 = [&](auto fun, int x) -> void {
        vis[x] = 1;
        for(auto i : g[x]) {
            if(!vis[i.fi]) {
                fun(fun, i.fi);
                chmax(dp[x][0], dp[i.fi][0] + i.se);
            }
        }
    };
    auto dfs2 = [&](auto fun, int x) -> void {
        vis[x] = 1;
        int tp = 0, g1 = 0, g2 = 0, g1p = 0, g2p = 0;
        for(auto i : g[x]) {
            if(!vis[i.fi]) {
                tp = dp[i.fi][0] + i.se;
                if(tp > g1) {
                    g2 = g1;
                    g2p = g1p;

                    g1 = tp;
                    g1p = i.fi;
                } else if(tp > g2) {
                    g2 = tp;
                    g2p = i.fi;
                }
            }   
        }
        if(x != 1) {
            tp = dp[x][1];
            if(tp > g1) {
                g2 = g1;
                g2p = g1p;

                g1 = tp;
                g1p = 0;
            } else if(tp > g2) {
                g2 = tp;
                g2p = 0;
            }
        }
        for(auto i : g[x]) {
            if(!vis[i.fi]) {
                if(i.fi == g1p)
                    dp[i.fi][1] = g2 + i.se;
                else
                    dp[i.fi][1] = g1 + i.se;
                fun(fun, i.fi);
            }
        }
    };
    while(std::cin >> n && n) {
        g = decltype(g) (n + 1, std::vector<std::pair<int, int>> ());
        rep(int, i, 1, n)
            dp[i][0] = dp[i][1] = 0;
        rep(int, u, 2, n) {
            std::cin >> v >> w;
            g[u].pb(v, w);
            g[v].pb(u, w);
        }
        std::fill(vis+1, vis+1+n, 0);
        dfs1(dfs1, 1);
        std::fill(vis+1, vis+1+n, 0);
        dfs2(dfs2, 1);
        rep(int, i, 1, n) {
            std::cout << std::max(dp[i][0], dp[i][1]) << nl;
        }
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