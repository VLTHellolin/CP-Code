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
constexpr static ll Mod = 998244353;
ll inv(ll x) { return fpow(x, Mod - 2, Mod) % Mod; }

class segment_tree {
private:
    class tree_node {
    public:
        ll num, sum, a;
    };
    int n;
    std::vector<tree_node> tr;
    std::vector<ll> lz;

    void update(int x=1) {
        tr[x].sum = (tr[x<<1].sum + tr[x<<1|1].sum + tr[x].num) % Mod;
    }
    void push_down(int x=1) {
        int a = fpow(2ll, lz[x], Mod), b = fpow(inv(2ll), lz[x], Mod);
        ((tr[x<<1].a += a - 1) *= b) %= Mod;
        ((tr[x<<1|1].a += a - 1) *= b) %= Mod;
        lz[x<<1] += lz[x];
        lz[x<<1|1] += lz[x];
        lz[x] = 0;
    }
public:
    explicit segment_tree(int _n)
        : n(_n) {
        tr.resize(n<<3|1);
        lz.resize(n<<3|1);
    }
    void modify(int l, int r, int lx, int rx, int x=1) {
        if(rx<l||r<lx) {
            tr[x].num = (tr[x].num + tr[x].a) * inv(2) % Mod;
            update(x);
            return;
        }
        if(l<=lx&&rx<=r) {
            ++lz[x];
            tr[x].num = (1 + tr[x].num) * inv(2) % Mod;
            tr[x].a = (1 + tr[x].a) * inv(2) % Mod;
            update(x);
            return;
        }
        (tr[x].num *= inv(2)) %= Mod;
        (tr[x].a *= inv(2)) %= Mod;
        int mid = (lx + rx) >> 1;
        push_down(x);
        modify(l, r, lx, mid, x<<1);
        modify(l, r, mid+1, rx, x<<1|1);
        update(x);
    }
    ll query(ll num) {
        return fpow(2ll, num, Mod) * tr[1].sum % Mod;
    }
};
int n, m, op, l, r, num;
void solve() {
    std::cin >> n;
    segment_tree tr(n);
    for(std::cin >> m; m--; [&](){
        std::cin >> op;
        if(op == 1) {
            ++num;
            std::cin >> l >> r;
            tr.modify(l, r, 1, n);
        } else {
            std::cout << tr.query(num) << nl;
        }
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