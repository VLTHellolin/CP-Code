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

class segment_tree {
private:
    int n;
    std::vector<bool> vis;
    std::vector<int> mx, pmx, a;
    std::vector<int> lz_sum, lz_asg, lz_mx, lz_ms;

    void push_down_sum(int f1, int f2, int x = 1) {
        if(vis[x]) {
            chmax(lz_mx[x], f2 + lz_asg[x]);
            lz_asg[x] += f1;
        } else {
            chmax(lz_ms[x], f2 + lz_sum[x]);
            lz_sum[x] += f1;
        }
        chmax(pmx[x], f2 + mx[x]);
        mx[x] += f1;
    }
    void push_down_asg(int f1, int f2, int x = 1) {
        mx[x] = lz_asg[x] = f1;
        if(vis[x]) {
            chmax(lz_mx[x], f2);
        } else {
            vis[x] = 1;
            lz_mx[x] = f2;
        }
        chmax(pmx[x], f2);
    }
    void push_down(int x = 1) {
        push_down_sum(lz_sum[x], lz_ms[x], x<<1);
        push_down_sum(lz_sum[x], lz_ms[x], x<<1|1);
        if(vis[x]) {
            vis[x] = 0;
            push_down_asg(lz_asg[x], lz_mx[x], x<<1);
            push_down_asg(lz_asg[x], lz_mx[x], x<<1|1);
            lz_asg[x] = lz_mx[x] = 0;
        } else {
            vis[x] = 0;
        }
        lz_sum[x] = lz_ms[x] = 0;
    }
    void update(int x = 1) {
        mx[x] = std::max(mx[x<<1], mx[x<<1|1]);
        pmx[x] = std::max(pmx[x<<1], pmx[x<<1|1]);
    }

    void build_tree(int l, int r, int x = 1) {
        if(l == r) {
            pmx[x] = mx[x] = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build_tree(l, mid, x<<1);
        build_tree(mid+1, r, x<<1|1);
        update(x);
    }

public:
    explicit segment_tree(int _n, std::vector<int> _a)
        : n(_n) {
        a = _a;
        vis.resize(n<<2|1);
        mx.resize(n<<2|1);
        pmx.resize(n<<2|1);
        lz_sum.resize(n<<2|1);
        lz_asg.resize(n<<2|1);
        lz_mx.resize(n<<2|1);
        lz_ms.resize(n<<2|1);
        build_tree(1, n);
    }
    int query(int l, int r, int lx, int rx, bool with_his = 0, int x = 1) {
        if(l <= lx && rx <= r) return with_his ? pmx[x] : mx[x];

        push_down(x);
        int mid = (lx + rx) >> 1;
        int ans = -5e8;
        if(l <= mid) chmax(ans, query(l, r, lx, mid, with_his, x<<1));
        if(r > mid) chmax(ans, query(l, r, mid+1, rx, with_his, x<<1|1));

        return ans;
    }
    void modify(int l, int r, int lx, int rx, int w, bool add = 0, int x = 1) {
        if(l <= lx && rx <= r) return add ? push_down_sum(w, w, x) : push_down_asg(w, w, x);

        push_down(x);
        int mid = (lx + rx) >> 1;
        if(l <= mid) modify(l, r, lx, mid, w, add, x<<1);
        if(r > mid) modify(l, r, mid+1, rx, w, add, x<<1|1);
        update(x);

    }
};
int n, q, x, y, z;
char op;
std::vector<int> a;
void solve() {
    std::cin >> n;
    a.resize(n+1);
    rep(int, i, 1, n) std::cin >> a[i];
    segment_tree tr(n, a);
    std::cin >> q;
    rep(int, i, 1, q) {
        std::cin >> op >> x >> y;
        if(x > y) std::swap(x, y);
        if(op == 'Q') {
            std::cout << tr.query(x, y, 1, n, 0) << nl;
        } else if(op == 'A') {
            std::cout << tr.query(x, y, 1, n, 1) << nl;
        } else if(op == 'P') {
            std::cin >> z;
            tr.modify(x, y, 1, n, z, 1);
        } else {
            std::cin >> z;
            tr.modify(x, y, 1, n, z, 0);
        }
    }
}
} // namespace hellolin