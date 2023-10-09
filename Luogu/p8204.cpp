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
constexpr int N = 1e6 + 11, B = 2000;
int n, m, fa[N], deg[N], son[N];
bool fro[N];
vec<std::tuple<int, int, int>> tmp[N];
vec<vec<int>> g;
void dfs_deg(int x, int f) {
    deg[x] = deg[f] + 1;
    for (auto &y : g[x]) {
        if (y != f) dfs_deg(y, x);
    }
}
pr<int, bool> dfs(int x) {
    pr<int, int> now{1, 0};
    for (auto &y : g[x]) {
        auto [a, b] = dfs(y);
        now.fi += a, now.se += b;
    }
    if (now.fi >= B || now.se > 1) {
        fro[x] = true;
        now.fi = 0;
    }
    if (!fro[x] && !now.se)
        return {now.fi, false};
    else
        return {now.fi, true};
}
int tot, qur;
str fiq;
char buf[100];
void mv(int x, int y) {
    ++tot, ++qur;
    sprintf(buf, "1 %d %d\n", x, y);
    fiq += buf;
}
void un() {
    --tot, ++qur;
    fiq += "2\n";
}
void as(int x) {
    ++qur;
    sprintf(buf, "3 %d\n", x);
    fiq += buf;
}
void solve() {
    std::cin >> n >> m;
    g.resize(n + 1);
    rep(i, 2, n) {
        std::cin >> fa[i];
        g[fa[i]].pb(i);
    }
    deg[0] = -1;
    dfs_deg(1, 0);
    dfs(1);
    rep(n) {
        if (fro[i]) {
            int f = i;
            while (f && !son[f]) {
                son[f] = i;
                f = fa[f];
            }
        }
    }
    rep(m) {
        int x, y;
        std::cin >> x >> y;
        if (y == 0) {
            as(i);
        } else if (son[x]) {
            tmp[son[x]].pb(i, x, y);
        } else {
            mv(x, y);
            as(i);
            un();
        }
    }
    rep(n) {
        if (fro[i] && tmp[i].size()) {
            std::sort(tmp[i].begin(), tmp[i].end(), [&](const auto &x, const auto &y) {
                auto &[t1, xa, xb] = x;
                auto &[t2, ya, yb] = y;
                int p = deg[xa] + xb, q = deg[ya] + yb;
                if (p == q)
                    return xa > ya;
                else
                    return p < q;
            });
            while (tot)
                un();
            for (auto &[t, a, b] : tmp[i]) {
                mv(i, std::max(deg[a] - deg[i] + b, 0));
                mv(a, b);
                as(t);
                un();
            }
        }
    }
    std::cout << qur << newl << fiq << newl;
}
} // namespace hellolin

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin.exceptions(std::cin.failbit);
    hellolin::solve();
    return 0;
}