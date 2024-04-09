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

#ifndef HELLOLIN_STRING_SUFFIX_ARRAY_HPP
#define HELLOLIN_STRING_SUFFIX_ARRAY_HPP 1
#include <string>
#include <vector>

namespace hellolin {

namespace string {

// ! 约定下标从 1 开始
class suffix_array {
    constexpr static int CHS = 127; // ASCII

public:
    std::vector<int> sa, rk;

private:
    int n, now, t;
    std::vector<int> oldsa, oldrk, key, tp;
    std::string s;

    void csort_1() {
        for (int i = 1; i <= n; i++)
            ++tp[rk[i] = s[i]];
        for (int i = 1; i <= CHS; i++)
            tp[i] += tp[i - 1];
        for (int i = n; i >= 1; i--)
            sa[tp[rk[i]]--] = i;
    }
    void csort_k(int k) {
        for (int i = 1; i <= n; i++)
            ++tp[key[i] = rk[oldsa[i]]];
        for (int i = 1; i <= k; i++)
            tp[i] += tp[i - 1];
        for (int i = n; i >= 1; i--)
            sa[tp[key[i]]--] = oldsa[i];
    }
    bool clash(int x, int y, int k) {
        return oldrk[x] == oldrk[y] && oldrk[x + k] == oldrk[y + k];
    }
    void set_sa() {
        csort_1();
        now = CHS;
        t = 0;
        for (int w = 1; t != n; w <<= 1, now = t) {
            int i = n;
            for (t = 0; i > n - w; i--)
                oldsa[++t] = i;
            for (i = 1; i <= n; i++)
                if (sa[i] > w) oldsa[++t] = sa[i] - w;

            std::fill(tp.begin(), tp.end(), 0);
            csort_k(now);

            std::copy(rk.begin(), rk.end(), oldrk.begin());
            for (t = 0, i = 1; i <= n; i++)
                rk[sa[i]] = clash(sa[i], sa[i - 1], w) ? t : ++t;
        }
    }

public:
    suffix_array() {}
    explicit suffix_array(std::string _s, int tp_size = 1e7) {
        set(_s, tp_size);
    }
    void set(std::string _s, int tp_size = 1e7) {
        s = _s;
        n = s.length();
        s = ' ' + s;
        sa.resize(n + 11, 0);
        rk.resize(n + 11, 0);
        oldsa.resize(n + 11, 0);
        oldrk.resize((n << 1) + 11, 0);
        key.resize(n + 11, 0);
        tp.resize(tp_size, 0);

        set_sa();
    }
};

} // namespace string

} // namespace hellolin

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
int n;
std::string s;
string::suffix_array sa;
void solve() {
    std::cin >> s;
    sa.set(s);
    n = s.size();
    rep(int, i, 1, n) std::cout << sa.sa[i] << " \n"[i == n];
}
} // namespace hellolin