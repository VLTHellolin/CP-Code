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
constexpr int N = 2e5 + 11, W = 30;
int n, m;
i64 ro, tot;
i64 l[N * W], r[N * W], tr[N * W][2];
i64 a[N];
void ins(i64 &t, int num, int deg) {
    if (!t) t = ++tot;
    r[t] = num;
    if (!l[t]) l[t] = num;
    if (~deg) ins(tr[t][(a[num] >> deg) & 1], num, deg - 1);
}
i64 gts(int t, int num, int deg) {
    i64 ans = 0;
    if (~deg) {
        int wd = (a[num] >> deg) & 1;
        if (tr[t][wd])
            ans += gts(tr[t][wd], num, deg - 1);
        else
            ans += (1 << deg) + gts(tr[t][wd ^ 1], num, deg - 1);
    }
    return ans;
}
i64 dfs(int t, int deg) {
    i64 ans = 0;
    if (~deg) {
        if (tr[t][0] && tr[t][1]) {
            ans = std::numeric_limits<i64>::max();
            rep(i, l[tr[t][0]], r[tr[t][0]])
                chmin(ans, (1 << deg) + gts(tr[t][1], i, deg - 1));
            ans += dfs(tr[t][0], deg - 1) + dfs(tr[t][1], deg - 1);
        } else if (tr[t][0]) {
            ans += dfs(tr[t][0], deg - 1);
        } else if (tr[t][1]) {
            ans += dfs(tr[t][1], deg - 1);
        }
    }
    return ans;
}
void solve() {
    std::cin >> n;
    rep(n) std::cin >> a[i];
    std::sort(a + 1, a + 1 + n);
    rep(n) ins(ro, i, W);
    std::cout << dfs(ro, W) << newl;
}
} // namespace hellolin

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin.exceptions(std::cin.failbit);
    hellolin::solve();
    return 0;
}