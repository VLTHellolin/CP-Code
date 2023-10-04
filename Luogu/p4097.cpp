/*
██╗  ██╗███████╗██╗     ██╗      ██████╗ ██╗     ██╗███╗   ██╗
██║  ██║██╔════╝██║     ██║     ██╔═══██╗██║     ██║████╗  ██║
███████║█████╗  ██║     ██║     ██║   ██║██║     ██║██╔██╗ ██║
██╔══██║██╔══╝  ██║     ██║     ██║   ██║██║     ██║██║╚██╗██║
██║  ██║███████╗███████╗███████╗╚██████╔╝███████╗██║██║ ╚████║
╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ ╚═════╝ ╚══════╝╚═╝╚═╝  ╚═══╝ 's CP Code Template!
Version 3.3.2.
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
#if defined(_WIN64) || defined(__x64_64__) || __WORDSIZE == 64
#define ARCH 64
#else
#define ARCH 32
#endif

namespace hellolin {
#define str std::string
#define vec std::vector
#define arr std::array
#define pr std::pair
using i8 = signed char;
using u8 = unsigned char;
using i16 = short;
using u16 = unsigned short;
using i32 = int;
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
#if ARCH == 64
using i128 = __int128;
using u128 = unsigned __int128;
#else
using i128 = i64;
using u128 = u64;
#endif
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
template <class T1, class T2>
inline bool chmax(T1 &x, T2 y) { return x < y ? x = y, 1 : 0; }
template <class T1, class T2>
inline bool chmin(T1 &x, T2 y) { return x > y ? x = y, 1 : 0; }
template <class T>
inline T read_next() {
    static std::decay_t<T> x;
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
constexpr i64 ModA = 39989, ModB = 1e9;
constexpr int N = 1e5 + 11;
constexpr ld eps = 1e-9;
template <class T>
int comp(T x, T y) {
    if (x - y >= eps) return 1;
    if (y - x >= eps) return -1;
    return 0;
}
template <class T>
ld conv(T x, int p)
    requires((bool) T(1, 1).fi && (bool) T(1, 1).se)
{
    return p * x.fi + x.se;
}
template <class T>
T _max(T x, T y)
    requires((bool) T(1, 1).fi && (bool) T(1, 1).se)
{
    int com{comp(x.fi, y.fi)};
    if (!com)
        return x.se < y.se ? x : y;
    else if (com > 0)
        return x;
    else
        return y;
}
class segment_tree {
private:
    vec<pr<ld, ld>> k;
    vi t;
    void update(int l, int r, int a, int x = 1) {
        int &b{t[x]};
        int mid{(l + r) >> 1};
        int com0{comp(conv(k[a], mid), conv(k[b], mid))};
        if ((com0 == 0 && a < b) || com0 > 0) std::swap(a, b);
        int com1{comp(conv(k[a], l), conv(k[b], l))}, com2{comp(conv(k[a], r), conv(k[b], r))};
        if ((com1 == 0 && a < b) || com1 > 0) update(l, mid, a, x << 1);
        if ((com2 == 0 && a < b) || com2 > 0) update(mid + 1, r, a, x << 1 | 1);
    }
    void maintain(int l, int r, int lx, int rx, int x = 1) {
        if (l <= lx && rx <= r) {
            update(lx, rx, k.size() - 1, x);
            return;
        }
        int mid{(lx + rx) >> 1};
        if (l <= mid) maintain(l, r, lx, mid, x << 1);
        if (r > mid) maintain(l, r, mid + 1, rx, x << 1 | 1);
    }

public:
    segment_tree() {
        t.resize(N << 1);
        k.pb(-1, -1);
    }
    void ins(pii px, pii py) {
        k.pb(-1, -1);
        auto &b = k.back();
        if (px.fi == py.fi)
            b = {0, std::max(px.se, py.se)};
        else {
            b.fi = 1.0 * (py.se - px.se) / (py.fi - px.fi);
            b.se = px.se - b.fi * px.fi;
        }
        maintain(px.fi, py.fi, 1, ModA);
    }
    pr<ld, int> query(int l, int r, int p, int x = 1) {
        if (p < l || r < p) return {0, 0};
        ld ans{conv(k[t[x]], p)};
        int mid{(l + r) >> 1};
        pr<ld, int> qwq{ans, t[x]};
        if (l == r) return qwq;
        return _max(qwq, _max(query(l, mid, p, x << 1), query(mid + 1, r, p, x << 1 | 1)));
    }
};
int q, op, lans, x;
pii px, py;
segment_tree st;
int temp;
void solve() {
//     freopen("/mnt/c/users/lin/downloads/p4097_11.in", "r", stdin);
//     freopen("/mnt/c/users/lin/downloads/p4097_11.out", "w", stdout);
    for (std::cin >> q; q--;) {
        std::cin >> op;
        auto func = [&](int &a, const int b) {
            a = ((lans + a - 1) % b + b) % b + 1;
        };
        if (op == 1) {
            std::cin >> px.fi >> px.se >> py.fi >> py.se;
            func(px.fi, ModA), func(px.se, ModB), func(py.fi, ModA), func(py.se, ModB);
            if (px.fi > py.fi)
                std::swap(px, py);
            st.ins(px, py);
        } else {
            std::cin >> x;
            // if(++temp == 205) std::cerr << x << newl;
            func(x, ModA);
            std::cout << (lans = st.query(1, ModA, x).se) << newl;
        }
    }
}
} // namespace hellolin