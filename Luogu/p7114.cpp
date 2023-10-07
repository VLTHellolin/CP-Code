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

#ifndef HELLOLIN_STRING_KMP_HPP
#define HELLOLIN_STRING_KMP_HPP 1
#include <string>
#include <vector>

namespace hellolin {

namespace string {

std::pair<std::vector<int>, std::vector<int>> kmp(std::string a, std::string b) {
    a = '#' + a, b = '#' + b;
    int n = a.size() - 1, m = b.size() - 1;
    std::vector<int> loc;
    std::vector<int> res(m + 1, 0);
    int j = 0;
    for (int i = 2; i <= m; ++i) {
        while (j && b[i] != b[j + 1])
            j = res[j];
        if (b[i] == b[j + 1]) ++j;
        res[i] = j;
    }
    j = 0;
    for (int i = 1; i <= n; ++i) {
        while (j && a[i] != b[j + 1])
            j = res[j];
        if (a[i] == b[j + 1]) ++j;
        if (j == m) {
            loc.push_back(i - m + 1);
            j = res[j];
        }
    }
    return {loc, res};
}

std::vector<int> z_function(std::string a) {
    a = '#' + a;
    int n = a.size() - 1;
    std::vector<int> z(n + 1, 0);
    z[1] = n;
    for (int l = 0, r = 0, i = 2; i <= n; ++i) {
        if (i <= r) z[i] = std::min(z[i - l + 1], r - i + 1);
        while (i + z[i] <= n && a[i + z[i]] == a[1 + z[i]])
            ++z[i];
        if (z[i] + i - 1 > r) {
            l = i;
            r = z[i] + i - 1;
        }
    }
    return z;
}

std::pair<std::vector<int>, std::vector<int>> ex_kmp(std::string a, std::string b) {
    std::vector<int> z = z_function(b);
    a = '#' + a, b = '#' + b;
    int n = a.size() - 1, m = b.size() - 1;
    std::vector<int> k(n + 1, 0);
    for (int l = 0, r = 0, i = 1; i <= n; ++i) {
        if (i <= r) k[i] = std::min(z[i - l + 1], r - i + 1);
        while (i + k[i] <= n && a[i + k[i]] == b[1 + k[i]])
            ++k[i];
        if (k[i] + i - 1 > r) {
            l = i;
            r = k[i] + i - 1;
        }
    }
    return {z, k};
}

} // namespace string

} // namespace hellolin

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

int T, n, pre, suf, tot, qwq[40];
bool bpre[40], bsuf[40];
i64 now1, now2, temp, ans;
str s;
// ds::fenwick_tree<int> tr;
void solve() {
    for (std::cin >> T; T--;) {
        std::cin >> s;
        auto z = string::z_function(s);

        s = '#' + s;
        n = s.size() - 1;
        pre = suf = tot = now1 = now2 = temp = ans = 0;
        // tr = decltype(tr) (40);
        memset(bpre, false, sizeof(bpre));
        memset(bsuf, false, sizeof(bsuf));
        memset(qwq, 0, sizeof(qwq));

        rep(n)
            bsuf[s[i] - 'a' + 1] ^= 1;
        rep(26)
            suf += bsuf[i];
        tot = suf;

        rep(n) {
            if(i == n) break;
            bool &npre = bpre[s[i] - 'a' + 1], &nsuf = bsuf[s[i] - 'a' + 1];
            if(npre) --pre;
            else ++pre;
            if(nsuf) {
                now1 -= qwq[suf--];
            } else {
                now1 += qwq[++suf];
            }
            npre ^= 1, nsuf ^= 1;

            temp = std::min((n - 1) / i, (z[i + 1] / i) + 1);
            ans += ((temp + 1) >> 1) * now1;
            ans += (temp >> 1) * now2;
            ++qwq[pre];
            if(pre <= suf) ++now1;
            if(pre <= tot) ++now2;
        }

        std::cout << ans << newl;
    }
}
} // namespace hellolin

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin.exceptions(std::cin.failbit);
    hellolin::solve();
    return 0;
}