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

#ifndef HELLOLIN_DS_DSU_HPP
#define HELLOLIN_DS_DSU_HPP 1
#include <algorithm>
#include <vector>

namespace hellolin {

namespace ds {

class dsu {
private:
    int n;
    std::vector<int> g;

public:
    dsu() {}
    explicit dsu(int _n)
        : n(_n) {
        g.resize(n + 1, 0);
        for(int i=0; i<=n; ++i) g[i] = i;
    }

    int find(int x) {
        return x == g[x] ? x : g[x] = find(g[x]);
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    void merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        // if (-g[x] < -g[y]) std::swap(x, y);
        g[x] = y;
        return;
    }
};

} // namespace ds

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

constexpr u64 Base = 114511, N = 1e6 + 11;
u64 fpow(u64 x, u64 y) {
    u64 res = 1;
    for(; y; y >>= 1, x *= x) res *= y & 1 ? x : 1;
    return res;
}
int T, n;
u64 ha1[N], ha2[N];
bool vis[N];
str s;
vec<pr<int,int>> res;
vec<int> ans;
ds::dsu d;
u64 g1(int l, int r) {
    return ha1[r] - ha1[l - 1] * fpow(Base, r - l + 1);
}
u64 g2(int l, int r) {
    return ha2[l] - ha2[r + 1] * fpow(Base, r - l + 1);
}
void solve() {
    for(std::cin >> T; T--; ) {
        std::cin >> s;
        n = s.size();
        s = '#' + s;
        res.clear();
        ans.clear();
        // ha1[0] = ha2[n + 1] = 0;
        d = ds::dsu(n + 1);
        rep(n) vis[i] = false;
        rep(n)
            ha1[i] = ha1[i - 1] * Base + s[i] - 'a' + 1;
        per(n)
            ha2[i] = ha2[i + 1] * Base + s[i] - 'a' + 1;
        int mid = n >> 1, j = 0;
        rep(n) {
            j = 0;
            if(i > mid) j = n - i + 1;
            else j = i;
            if(g1(i - j + 1, i) == g2(i, i + j - 1)) {
                res.pb(i, j);
                vis[i] = true;
                // vis[j] = true;
            }
        }
        for(auto &i : res) {
            if(vis[i.fi + i.se - 1]) {
                d.merge(i.fi, i.fi + i.se - 1);
            }
        }
        rep(n) {
            int f = d.find(i);
            if(f > mid)
                if(vis[f])
                    ans.pb(i);
        }
        for(auto &i : ans) std::cout << i << ' ';
        std::cout << newl;
    }
}
} // namespace hellolin

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin.exceptions(std::cin.failbit);
    hellolin::solve();
    return 0;
}