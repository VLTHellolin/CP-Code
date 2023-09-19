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
ll a, b, n;
std::vector<int> d;
ll dp[20][10][10];
// dp[i][j][k]: length=i, topmost number=j, ks' count
ll get_ans(ll num, int w) {
    ll ans = 0;
    d.clear();
    d.pb(0); // pos 0
    do {
        d.pb(num % 10);
        num /= 10;
    } while(num);
    n = d.size() - 1;
    rep(int, i, 1, n - 1) { // length lt n
        rep(int, j, 1, 9)
            ans += dp[i][j][w];
    }
    rep(int, i, 1, (*d.rbegin()) - 1) // length eq n, topmost number lt topmost target
        ans += dp[n][i][w];
    per(int, i, n - 1, 1) { // length eq n, 1st number eq 1st target
        rep(int, j, 0, d[i] - 1) // ist number lt ist target
            ans += dp[i][j][w];
        per(int, j, n, i+1) // ist number geq ist target
            if(d[j] == w) ans += d[i] * fpow(10ll, i-1);
    }

    return ans;
}
void solve() {
    std::cin >> a >> b;
    rep(int, i, 0, 9) // when length=1, only i itself meets the conditions
        dp[1][i][i] = 1;
    rep(int, i, 2, 14) {
        rep(int, jx, 0, 9) { // the topmost number
            rep(int, jy, 0, 9) // another topmost number
                rep(int, k, 0, 9)
                    dp[i][jx][k] += dp[i - 1][jy][k];
            dp[i][jx][jx] += fpow(10ll, i-1);
        }
    }
    rep(int, x, 0, 9)
        std::cout << get_ans(b+1, x) - get_ans(a, x) << " \n"[x==9];
    
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