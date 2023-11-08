/*
 * |-| [- |_ |_ () |_ | |\| 's Competitive Code Template v3.4.1
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
using i8 = int8_t;
using u8 = u_int8_t;
using i16 = int16_t;
using u16 = u_int16_t;
using i64 = int64_t;
using u64 = u_int64_t;
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
constexpr int N = 5005;
int n, m;
char res[N][N];
bool a, b, sw;
void solve() {
    std::cin >> n >> m;
    a = n & 1;
    b = m & 1;

    if (a && b) {
        // No solution. Ans will always be 0.
        rep(i, n)
            rep(j, m)
                res[i][j] = '(';
    } else if (a && !b) {
        // Construct row-brackets.
        rep(i, n) {
            rep(j, 1, m, 2) {
                res[i][j] = '(';
                res[i][j + 1] = ')';
            }
        }
    } else if (!a && b) {
        // Construct col-brackets.
        rep(j, m) {
            rep(i, 1, n, 2) {
                res[i][j] = '(';
                res[i + 1][j] = ')';
            }
        }
    } else {
        // Construct row-brackets, and then construct as many col-brackets as we can.
        // Compare it with col-brackets first's solution.
        if (n > m) {
            std::swap(n, m);
            sw = true;
        }
        rep(j, m) {
            res[1][j] = '(';
            res[n][j] = ')';
        }
        rep(i, 2, n - 1) {
            if(n >= 6) {
                res[i][1] = '(';
                res[i][m] = ')';
                rep(j, 2, m - 1)
                    res[i][j] = ((i + j) & 1) ? '(' : ')';
            } else {
                rep(j, m)
                    res[i][j] = ((i + j) & 1) ? '(' : ')';
            }
        }
    }

    // Output.
    if(sw) {
        rep(j, m) {
            rep(i, n) {
                std::cout << res[i][j];
            }
            std::cout << newl;
        }
    } else {
        rep(i, n) {
            rep(j, m) {
                std::cout << res[i][j];
            }
            std::cout << newl;
        }
    }
}
} // namespace hellolin

int main() {
#ifndef LOCAL
    freopen("butterfly.in", "r", stdin);
    freopen("butterfly.out", "w", stdout);
#endif
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin.exceptions(std::cin.failbit);
    hellolin::solve();
    return 0;
}