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

#ifndef HELLOLIN_DS_DSU_HPP
#define HELLOLIN_DS_DSU_HPP 1
#include <algorithm>
#include <vector>

namespace hellolin {

namespace ds {

class dsu {
private:
    int n;
    std::vector<int> g, sz;

public:
    dsu() {}
    explicit dsu(int _n)
        : n(_n) {
        g.resize(n + 1);
        for (int i = 1; i <= n; i++)
            g[i] = i;
        sz.resize(n + 1, 1);
    }

    int find(int x) {
        return x == g[x] ? x : g[x] = find(g[x]);
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    int size(int x) {
        return sz[find(x)];
    }
    void merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (sz[x] < sz[y]) std::swap(x, y);
        sz[x] += sz[y];
        g[y] = x;
    }
    void erase(int x) {
        --sz[find(x)];
        g[x] = x;
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
constexpr int N = 5e5 + 114;
bool comp_mode;
class edge {
public:
    int x, y, w = -1, num, a, b;
    edge() {}
    explicit edge(int _x, int _y, int _w, int _num = -1, int _a = 0, int _b = 0)
        : x(_x)
        , y(_y)
        , w(_w)
        , num(_num)
        , a(_a)
        , b(_b) {}
    bool operator<(const edge &e) const {
        if (comp_mode) return num < e.num;
        return w < e.w;
    }
    bool operator>(const edge &e) const {
        if (comp_mode) return num > e.num;
        return w > e.w;
    }
    friend std::istream &operator>>(std::istream &is, edge &e) {
        is >> e.x >> e.y >> e.w;
        return is;
    }
    void fd(ds::dsu &s) {
        a = s.find(x);
        b = s.find(y);
    }
} ed[N];
int n, m, q;
ds::dsu d;
bool ans;
void solve() {
    std::cin >> n >> m;
    d = ds::dsu(n);
    rep(m) {
        ed[i].num = i;
        std::cin >> ed[i];
    }
    std::sort(ed + 1, ed + 1 + m);
    for (int i = 1, j = 1; i <= m;) {
        j = i;
        do {
            ed[j++].fd(d);
        } while (j <= m && ed[j - 1].w == ed[j].w);
        while (i < j) {
            while (d.same(ed[i].x, ed[i].y) && i < j)
                ++i;
            if (i < j)
                d.merge(ed[i].x, ed[i].y);
        }
    }
    comp_mode = true;
    std::sort(ed + 1, ed + 1 + m);
    d = ds::dsu(n);
    comp_mode = false;
    for (std::cin >> q; q--;) {
        int k;
        vec<edge> p;
        std::cin >> k;
        rep(k) {
            int x;
            std::cin >> x;
            p.pb(ed[x].a, ed[x].b, ed[x].w);
        }
        ans = true;
        std::sort(p.begin(), p.end());
        for (int i = 0, j = 0; i < (int) p.size();) {
            if (p[i].x == p[i].y) {
                ans = false;
                break;
            }
            d.merge(p[i].x, p[i].y);
            j = i + 1;
            while (j < (int) p.size() && p[i].w == p[j].w) {
                if (d.same(p[j].x, p[j].y)) {
                    ans = false;
                    break;
                }
                d.merge(p[j].x, p[j].y);
                ++j;
            }
            while (i < j) {
                d.erase(p[i].x), d.erase(p[i].y);
                ++i;
            }
        }
        std::cout << (ans ? "YES" : "NO") << newl;
    }
}
} // namespace hellolin

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin.exceptions(std::cin.failbit);
    hellolin::solve();
    return 0;
}