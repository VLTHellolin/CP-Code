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
constexpr int N = 2e6 + 11, W = 23;
int q, cnt;
struct fenwick_tree {
    int tr[N];
    void add(int x, int y) {
        for(; x <= cnt; x += x & -x)
            tr[x] += y;
    }
    int sum(int x) {
        int res = 0;
        for(; x >= 1; x -= x & -x)
            res += tr[x];
        return res;
    }
} ice, fire;
pr<int, int> od[N];
int kice, kfire, sice, sfire;
int ic[N], fi[N];
struct info {
    int op, k, x, y;
} qur[N];
void solve() {
    std::cin >> q;
    rep(q) {
        std::cin >> qur[i].op >> qur[i].k;
        if(qur[i].op == 1) {
            std::cin >> qur[i].x >> qur[i].y;
            od[++cnt] = {qur[i].x, i};
        }
    }
    std::sort(od+1, od+1+cnt);
    int tp = 1;
    rep(q) {
        if(od[i - 1].fi != od[i].fi)
            tp = i;
        qur[od[i].se].x = tp;
    }
    rep(q) {
        if(qur[i].op == 1) {
            if(qur[i].k == 0) {
                ++kice;
                ice.add(qur[i].x, qur[i].y);
                sice += qur[i].y;
                ic[qur[i].x] += qur[i].y;
            } else {
                ++kfire;
                fire.add(qur[i].x, qur[i].y);
                sfire += qur[i].y;
                fi[qur[i].x] += qur[i].y;
            }
        } else {
            tp = qur[i].k;
            if(qur[tp].k == 0) {
                --kice;
                ice.add(qur[tp].x, -qur[tp].y);
                sice -= qur[tp].y;
                ic[qur[tp].x] -= qur[tp].y;
            } else {
                --kfire;
                fire.add(qur[tp].x, -qur[tp].y);
                sfire -= qur[tp].y;
                fi[qur[tp].x] -= qur[tp].y;
            }
        }
        if(kice == 0 || kfire == 0) {
            std::cout << "Peace" << newl;
            continue;
        }
        tp = 0;
        int tp2 = 0;
        per(j, W, 0) {
            int now = (1 << j) | tp;
            if(now <= cnt) {
                if(tp2 + ice.tr[now] + fire.tr[now] - fi[now] <= sfire) {
                    tp = now;
                    tp2 += ice.tr[tp] + fire.tr[tp];
                }
            }
        }
        auto conv = [&](const int &x) {
            if(x < 1 || x > cnt) return -1;
            else return std::min(ice.sum(x), sfire - fire.sum(x - 1));
        };
        int pc = conv(tp), cp = conv(tp + 1);
        if(pc <= 0 && cp <= 0) {
            std::cout << "Peace" << newl;
        } else if(pc > cp) {
            std::cout << od[tp].fi << ' ' << (pc * 2) << newl;
        } else {
            tp = 0;
            tp2 = 0;
            per(j, W, 0) {
                int now = (1 << j) | tp;
                if(now <= cnt)
                    if(sfire - tp2 - fire.tr[now] + fi[now] >= cp) {
                        tp = now;
                        tp2 += fire.tr[tp];
                    }
            }
            std::cout << od[tp].fi << ' ' << (cp * 2) << newl;
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