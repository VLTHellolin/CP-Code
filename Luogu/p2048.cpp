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
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
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
constexpr static int N = 5e5 + 11, LN = 25;
int x, pre[N];
class ST {
private:
    int st[N][LN];
public:
    explicit ST(int n) {
        rep(int, i, 1, n) st[i][0] = i;
        for(int j = 1; (1 << j) <= n; ++j) {
            for(int i = 1; (1 << j) + i - 1 <= n; ++i) {
                int l = st[i][j - 1], r = st[i + (1 << (j - 1))][j - 1];
                st[i][j] = pre[l] < pre[r] ? r : l;
            }
        }
    }
    int query(int a, int b) {
        int len = b - a + 1, lg = log2(len);
        int l = st[a][lg], r = st[b + 1 - (1 << lg)][lg];
        return pre[l] < pre[r] ? r : l;
    }
};
ST *qwq;
class res {
private:
    int l, r;
    int rl = 0, rr;
public:
    explicit res(int _l, int _r, int _rl)
        : l(_l)
        , r(_r)
        , rl(_rl) {
        rr = qwq->query(l, r);
    }
    int query() const {
        return pre[rr] - pre[rl - 1];
    }
    bool operator<(const res &t) const {
        return query() < t.query();
    }
    bool appor(bool wi) { return (wi ? r : l) == rr; }
    res ls() {
        return res(l, rr - 1, rl);
    }
    res rs() {
        return res(rr + 1, r, rl);
    }
};
int n, k, l, r;
ll ans;
__gnu_pbds::priority_queue<res, std::less<res>> pq;
void solve() {
    std::cin >> n >> k >> l >> r;
    rep(int, i, 1, n) {
        std::cin >> x;
        pre[i] = pre[i - 1] + x;
    }
    qwq = new ST(n);
    rep(int, i, 1, n) {
        int al = i + l - 1, ar = i + r - 1;
        if(al <= n) pq.push(res(al, std::min(ar, n), i));
    }
    rep(int, i, 1, k) {
        res tp = pq.top();
        pq.pop();
        ans += tp.query();
        if(!tp.appor(0)) pq.push(tp.ls());
        if(!tp.appor(1)) pq.push(tp.rs());
    }
    std::cout << ans << nl;

}
} // namespace hellolin