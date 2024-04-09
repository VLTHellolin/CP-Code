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
constexpr static ll N = 1e7 + 11, Mod = 20101009;
bool vis[N];
std::vector<ll> pr;
ll mu[N], ans;
int n, m;
void solve() {
    auto calc = [&](ll x) {
        return x * (x + 1) / 2 % Mod;
    };
    mu[1] = 1;
    rep(int, i, 2, 1e7) {
        if(!vis[i]) {
            mu[i] = (1 - i + Mod) % Mod;
            pr.pb(i);
        }
        for(ll &j : pr) {
            if(i * j > 1e7) break;
            vis[i * j] = 1;
            if(i % j == 0) {
                mu[i * j] = mu[i];
                break;
            }
            mu[i * j] = mu[i] * mu[j] % Mod;
        } 
    }
    rep(int, i, 1, 1e7) (mu[i] = mu[i-1] + mu[i] * i % Mod) %= Mod;
    std::cin >> n >> m;
    if(n>m) std::swap(n, m);
    int l = 1, r = 1;
    for(; l <= n; l = r + 1) {
        r = std::min(n / (n / l), m / (m / l));
        (ans += (mu[r] - mu[l-1] + Mod) % Mod * calc(n / l) % Mod * calc(m / l) % Mod) %= Mod;
    }
    std::cout << ans << nl;
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