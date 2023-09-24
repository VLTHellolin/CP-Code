// * HELLOLIN'S CP CODE TEMPLATE v3.0.1     * //
// * https://github.com/hellolin-oi/CP-Code * //
#ifndef ONLINE_JUDGE
#pragma warning(disable: 4018)
#pragma warning(disable: 4068)
#pragma warning(disable: 4800)
#pragma GCC optimize(2, "inline", "unroll-loops", "no-stack-protector", "-ffast-math")
#pragma GCC target("avx2,lzcnt,popcnt")
#endif
#include <bits/stdc++.h>
// #include "atcoder/all"

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
constexpr static int N = 30;
int n, m;
char x;
int u, v, ind[N], cnt;
std::vector<std::vector<int>> g;
std::queue<int> q;
std::vector<int> res, hv;
int bfs() {
    // 0 : ok
    // 1 : cannot be determinded
    // 2 : inconsistency was founded
    q = decltype(q) ();
    res.clear();
    bool flag = 0;
    cnt = 0;
    rep(int, i, 1, n) {
        if(!ind[i]) {
            q.ps(i);
            ++cnt;
        }
    }
    if(cnt > 1) flag = 1;
    while(q.size()) {
        int x = q.front();
        q.pop();
        cnt = 0;
        res.pb(x);
        for(int y : g[x]) {
            if(--ind[y] == 0) {
                q.ps(y);
                ++cnt;
            }
        }
        if(cnt > 1) flag = 1;
    }
    if(res.size() != n) return 2;
    if(flag) return flag;
    return 0;

}
void solve() {
    std::cin >> n >> m;
    g.resize(n+1);
    rep(int, i, 1, m) {
        std::cin >> x;
        u = x - 'A' + 1;
        std::cin >> x >> x;
        v = x - 'A' + 1;
        hv.pb(v);

        memset(ind, 0, sizeof(ind));
        for(int j : hv) ++ind[j];
        g[u].pb(v);
        int ans = bfs();
        if(ans == 0) {
            std::cout << "Sorted sequence determined after " << i << " relations: ";
            for(int j : res) {
                std::cout << char(j + 'A' - 1);
            }
            std::cout << ".\n";
            return;
        } else if(ans == 2) {
            std::cout << "Inconsistency found after " << i << " relations.\n";
            return;
        }
    }
    std::cout << "Sorted sequence cannot be determined.\n";

}
} // namespace hellolin