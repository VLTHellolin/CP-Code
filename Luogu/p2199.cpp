/*
 * |-| [- |_ |_ () |_ | |\| 's Competitive Code Template v3.4.2
 * Recommended standard: C++20.
 * In general, this source code can be found archived here:
 *     https://github.com/hellolin-oi/CP-Code
 */
#ifndef ONLINE_JUDGE
#pragma GCC optimize(2, "inline", "unroll-loops", "no-stack-protector", "fast-math")
#endif
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,lzcnt,popcnt")
#include <bits/stdc++.h>
#include <emmintrin.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <immintrin.h>
// #include "atcoder/all"
#if defined(_WIN64) || defined(__x86_64__) || __WORDSIZE == 64
#define ARCH64
#endif

namespace hellolin {
#define str std::string
#define vec std::vector
#define pr std::pair
#define pq __gnu_pbds::priority_queue
using i8 = signed char;
using u8 = unsigned char;
using i16 = short;
using u16 = unsigned short;
using i64 = long long;
using u64 = unsigned long long;
#ifdef ARCH64
using i128 = __int128_t;
using u128 = __uint128_t;
#else
#warning The int128 type has been fallbacked to int64.
using i128 = i64;
using u128 = u64;
#endif
using ld = long double;
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
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define fi first
#define se second
#define ps emplace
#define pb emplace_back
constexpr char newl = '\n';
template <class T1, class T2>
inline bool chmax(T1 &x, T2 y) { return x < y ? x = y, 1 : 0; }
template <class T1, class T2>
inline bool chmin(T1 &x, T2 y) { return x > y ? x = y, 1 : 0; }
constexpr int NM = 2e4 + 11;
int n, m;
bool p[NM];
int vis[NM];
int dx[9] = {114514, 1, 1, 1, 0, 0, -1, -1, -1};
int dy[9] = {114514, -1, 0, 1, -1, 1, -1, 0, 1};
int ex[5] = {114514, 1, -1, 0, 0};
int ey[5] = {114514, 0, 0, 1, -1};
std::queue<std::tuple<int, int, int>> q;
int conv(int x, int y) {
    return (x - 1) * m + y;
}
void clear() {
    q = decltype(q)();
    rep(n) rep(j, m) vis[conv(i, j)] = 0;
}
void qe(int x, int y) {
    rep(_, 1, 8) {
        int nx = x, ny = y;
        nx += dx[_], ny += dy[_];
        while (nx >= 1 && nx <= n && ny >= 1 && ny <= m && !p[conv(nx, ny)]) {
            vis[conv(nx, ny)] = 1;
            nx += dx[_], ny += dy[_];
        }
    }
}
int bfs(int _x, int _y) {
    q.ps(_x, _y, 0);
    while (q.size()) {
        auto [x, y, c] = q.front();
        // debug("Current {%d, %d}, %d\n", x, y, c);
        q.pop();
        rep(_, 1, 4) {
            int nx = x + ex[_], ny = y + ey[_];
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && !p[conv(nx, ny)] && vis[conv(nx, ny)] != 2) {
                if (vis[conv(nx, ny)] == 1)
                    return c + 1;
                vis[conv(nx, ny)] = 2;
                q.ps(nx, ny, c + 1);
            }
        }
    }
    return -1;
}
void solve() {
    std::cin >> n >> m;
    rep(n) {
        rep(j, m) {
            char t;
            std::cin >> t;
            p[conv(i, j)] = t == 'X';
        }
    }
    int ax, ay, bx, by;
    while (std::cin >> ax >> ay >> bx >> by) {
        if (ax + ay + bx + by == 0) return;
        clear();
        vis[conv(ax, ay)] = 1;
        qe(ax, ay);
        if (vis[conv(bx, by)]) {
            std::cout << 0 << newl;
        } else {
            int ans = bfs(bx, by);
            if (~ans)
                std::cout << ans << newl;
            else
                std::cout << "Poor Harry" << newl;
        }
    }
}
} // namespace hellolin

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin.exceptions(std::cin.failbit);
    hellolin::solve();
    return 0;
}