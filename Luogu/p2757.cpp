/*
██╗  ██╗███████╗██╗     ██╗      ██████╗ ██╗     ██╗███╗   ██╗
██║  ██║██╔════╝██║     ██║     ██╔═══██╗██║     ██║████╗  ██║
███████║█████╗  ██║     ██║     ██║   ██║██║     ██║██╔██╗ ██║
██╔══██║██╔══╝  ██║     ██║     ██║   ██║██║     ██║██║╚██╗██║
██║  ██║███████╗███████╗███████╗╚██████╔╝███████╗██║██║ ╚████║
╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ ╚═════╝ ╚══════╝╚═╝╚═╝  ╚═══╝ 's CP Code Template!
Version 3.3.0.
Recommended standard: C++20. Minimum standard: C++17.
In general, this source code can be found archived here: https://github.com/hellolin-oi/CP-Code
The main code section is at the end of this file.
*/
#ifndef ONLINE_JUDGE
#pragma warning(disable : 4018)
#pragma warning(disable : 4068)
#pragma warning(disable : 4800)
#pragma GCC optimize(2, "inline", "unroll-loops", "no-stack-protector", "-ffast-math")
#pragma GCC target("sse4,avx2,lzcnt,popcnt")
#endif
#include <bits/stdc++.h>
// #include "atcoder/all"

namespace hellolin {
#define vec std::vector
#define arr std::array
#define pr std::pair
using i8 = signed char;
using i16 = short;
using i32 = int;
using i64 = long long;
using i128 = __int128;
using ld = long double;
using vi = vec<int>;
using vvi = vec<vi>;
using pii = pr<int, int>;
#define rdecltype(x) std::decay_t<decltype(x)>
#define _rep1(x) for (rdecltype(x) i = 1, i##end = x; i <= i##end; ++i)
#define _rep2(i, x) for (rdecltype(x) i = 1, i##end = x; i <= i##end; ++i)
#define _rep3(i, x, y) for (auto i = x, i##end = y; i <= i##end; ++i)
#define _rep4(i, x, y, z) for (auto i = x, i##end = y; i <= i##end; i += (z))
#define _per1(x) for (rdecltype(x) i = x, i##end = 1; i >= i##end; --i)
#define _per2(i, x) for (rdecltype(x) i = x, i##end = 1; i >= i##end; --i)
#define _per3(i, x, y) for (auto i = x, i##end = y; i >= i##end; --i)
#define _per4(i, x, y, z) for (auto i = x, i##end = y; i >= i##end; i -= (z))
#define ovld(_1, _2, _3, _4, x, ...) x
#define rep(...) ovld(__VA_ARGS__, _rep4, _rep3, _rep2, _rep1)(__VA_ARGS__)
#define per(...) ovld(__VA_ARGS__, _per4, _per3, _per2, _per1)(__VA_ARGS__)
#define fec(i, x) for (auto &i : x)
template <class T1, class T2>
inline bool chmax(T1 &x, T2 y) { return x > y ? x = y, 1 : 0; }
template <class T1, class T2>
inline bool chmin(T1 &x, T2 y) { return x < y ? x = y, 1 : 0; }
template <class T>
inline T read_next() {
    static T x;
    return std::cin >> x, x;
}
template <class T>
inline void read_arr(T x, int n) {
    std::generate_n(x, n, [&] { return read_next<rdecltype(*x)>(); });
}
template <class T>
inline void write_arr(T x, int n, char sep = ' ', char end = '\n') {
    static int cnt = 0;
    std::for_each_n(x, n, [&](const auto &x) { std::cout << x << (++cnt == n ? end : sep); });
}
inline void _debug() { std::cerr << '\n'; }
template <class T, class... Args>
inline void _debug(T x, Args... y) {
    std::cerr << x << ' ';
    _debug(y...);
}
#ifndef ONLINE_JUDGE
#define debug _debug
#else
#define debug \
    if (0) _debug
#endif
#define fi first
#define se second
#define lowbit(x) (x & -x)
#define ps emplace
#define pb emplace_back
constexpr char newl = '\n';
void solve();
} // namespace hellolin

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin.exceptions(std::cin.failbit);
    hellolin::solve();
    return 0;
}

namespace hellolin {
constexpr int N = 5e5 + 11;
constexpr i64 HashBase = 114511, HashMod = 998244353;
int hs[N];
inline i64 hash_of(i64 y) {
    // i64 x = HashBase, res = 1;
    // for (; y; y >>= 1, (x *= x) %= HashMod)
    //     if (y & 1) (res *= x) %= HashMod;
    // return res;
    return hs[y];
}
class segment_tree {
private:
    int n;
    struct tree_node {
        int len1 = 1, len2 = 1;
        int has1 = 0, has2 = 0;
        tree_node(i64 h = 0)
            : has1(h)
            , has2(h) {}
        tree_node operator+(const tree_node &t) const {
            tree_node res;
            res.len1 = len1 + t.len1;
            res.len2 = len2 + t.len2;
            res.has1 = (t.has1 + has1 * hash_of(t.len1) % HashMod) % HashMod;
            res.has2 = (has2 + t.has2 * hash_of(len2) % HashMod) % HashMod;
            return res;
        }
        tree_node &operator+=(const tree_node &t) {
            return *this = *this + t;
        }
    };
    vec<tree_node> tr;

    void update(int x = 1) {
        tr[x] = tr[x << 1] + tr[x << 1 | 1];
    }
    void build_tree(int l, int r, int x = 1) {
        if (l == r) return;
        int mid = (l + r) >> 1;
        build_tree(l, mid, x << 1);
        build_tree(mid + 1, r, x << 1 | 1);
        update(x);
    }

public:
    explicit segment_tree(int _n)
        : n(_n) {
        tr.resize(n << 2 | 1);
        build_tree(1, n);
    }
    void maintain(int p, int l, int r, int x = 1) {
        if (l == r) {
            tr[x] = tree_node{1};
            return;
        }
        int mid = (l + r) >> 1;
        if (p <= mid) maintain(p, l, mid, x << 1);
        if (p > mid) maintain(p, mid + 1, r, x << 1 | 1);
        update(x);
    }
    tree_node query(int l, int r, int lx, int rx, int x = 1) {
        if (l <= lx && rx <= r) return tr[x];
        int mid = (lx + rx) >> 1;
        // tree_node ans;
        // if(r <= mid) ans += query(l, r, lx, mid, x<<1);
        // if(l > mid) ans += query(l, r, mid+1, rx, x<<1|1);
        // return ans;
        if (r <= mid) return query(l, r, lx, mid, x << 1);
        if (l > mid) return query(l, r, mid + 1, rx, x << 1 | 1);
        return query(l, r, lx, mid, x << 1) + query(l, r, mid + 1, rx, x << 1 | 1);
    }
};
int T, n;
int a[N];
bool ans;
void solve() {
    hs[0] = 1;
    for (std::cin >> T; T--;) {
        std::cin >> n;
        rep(n) hs[i] = hs[i - 1] * HashBase % HashMod;
        read_arr(a + 1, n);
        segment_tree tr(n);
        ans = 0;
        rep(n) {
            int len = std::min(n - a[i], a[i] - 1);
            tr.maintain(a[i], 1, n);
            if(len <= 0) continue;
            if (tr.query(a[i] - len, a[i] - 1, 1, n).has1 != tr.query(a[i] + 1, a[i] + len, 1, n).has2) {
                ans = 1;
                break;
            }
        }
        std::cout << (ans ? 'Y' : 'N') << newl;
    }
}
} // namespace hellolin