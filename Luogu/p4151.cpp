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

#ifndef HELLOLIN_MATH_BASIS_HPP
#define HELLOLIN_MATH_BASIS_HPP 1
#include <vector>

namespace hellolin {

namespace math {

class basis {
    using val_type = unsigned long long;

private:
    std::vector<val_type> a;

public:
    basis() { a.resize(64, 0); }
    void insert(val_type x) {
        for (int i = 63; ~i; --i) {
            if (!(x >> i)) continue;
            if (!a[i]) {
                a[i] = x;
                break;
            }
            x ^= a[i];
        }
    }
    val_type query(val_type x = 0) {
        val_type res = x;
        for (int i = 63; ~i; --i) {
            if ((res ^ a[i]) > res)
                res ^= a[i];
        }
        return res;
    }
};

} // namespace math

} // namespace hellolin

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
constexpr int N = 5e4 + 114;
math::basis ba;
int n, m, u, v;
i64 w, t[N];
bool vis[N];
vec<vec<pr<int,i64>>> g;
void dfs(int x, int fa, i64 now) {
    t[x] = now;
    vis[x] = 1;
    for(auto i : g[x]) {
        if(i.fi != fa) {
            if(vis[i.fi]) ba.insert(t[i.fi] ^ now ^ i.se);
            else dfs(i.fi, x, now ^ i.se);

        }
    }
}
void solve() {
    std::cin >> n >> m;
    g.resize(n+1);
    rep(m) {
        std::cin >> u >> v >> w;
        g[u].pb(v, w);
        g[v].pb(u, w);
    }
    dfs(1, 0, 0);
    std::cout << (ba.query(t[n])) << newl;

}
} // namespace hellolin