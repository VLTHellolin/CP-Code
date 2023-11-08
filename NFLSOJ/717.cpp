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
constexpr int N = 2e6 + 11;
int n, q;
namespace segment_tree {
pr<int, int> tr[N << 2];
vec<int> res;
void update(int x) {
    tr[x] = {std::max(tr[x << 1].fi, tr[x << 1 | 1].fi), std::min(tr[x << 1].se, tr[x << 1 | 1].se)};
}
void push_down(int x) {
    auto &rt = tr[x], &ls = tr[x << 1], &rs = tr[x << 1 | 1];
    chmin(ls.fi, rt.fi);
    chmin(ls.se, rt.fi);
    chmax(ls.fi, rt.se);
    chmax(ls.se, rt.se);
    chmin(rs.fi, rt.fi);
    chmin(rs.se, rt.fi);
    chmax(rs.fi, rt.se);
    chmax(rs.se, rt.se);
}
void build_tree(int l, int r, int x = 1) {
    if (l == r) {
        tr[x] = {0, 0};
        return;
    }
    int mid = (l + r) >> 1;
    build_tree(l, mid, x << 1);
    build_tree(mid + 1, r, x << 1 | 1);
    update(x);
}
void modify(int l, int r, int lx, int rx, int w, int f, int x = 1) {
    if (l <= lx && rx <= r) {
        if (f == 1) {
            chmax(tr[x].fi, w);
            chmax(tr[x].se, w);
        } else {
            chmin(tr[x].fi, w);
            chmin(tr[x].se, w);
        }
        return;
    }
    int mid = (lx + rx) >> 1;
    push_down(x);
    if (l <= mid) modify(l, r, lx, mid, w, f, x << 1);
    if (r > mid) modify(l, r, mid + 1, rx, w, f, x << 1 | 1);
    update(x);
}
void query(int l, int r, int x = 1) {
    if (l == r) {
        res.pb(tr[x].fi);
        return;
    }
    int mid = (l + r) >> 1;
    push_down(x);
    query(l, mid, x << 1);
    query(mid + 1, r, x << 1 | 1);
}

} // namespace segment_tree
void solve() {
    std::cin >> n >> q;
    segment_tree::build_tree(1, n);
    while (q--) {
        int op, l, r, h;
        std::cin >> op >> l >> r >> h;
        segment_tree::modify(l + 1, r + 1, 1, n, h, op);
    }
    segment_tree::query(1, n);
    for (auto &i : segment_tree::res) {
        std::cout << i << newl;
    }
}
} // namespace hellolin

int main() {
#ifndef LOCAL
    freopen("wall.in", "r", stdin);
    freopen("wall.out", "w", stdout);
#endif
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin.exceptions(std::cin.failbit);
    hellolin::solve();
    return 0;
}