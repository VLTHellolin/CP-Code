/*
██╗  ██╗███████╗██╗     ██╗      ██████╗ ██╗     ██╗███╗   ██╗
██║  ██║██╔════╝██║     ██║     ██╔═══██╗██║     ██║████╗  ██║
███████║█████╗  ██║     ██║     ██║   ██║██║     ██║██╔██╗ ██║
██╔══██║██╔══╝  ██║     ██║     ██║   ██║██║     ██║██║╚██╗██║
██║  ██║███████╗███████╗███████╗╚██████╔╝███████╗██║██║ ╚████║
╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ ╚═════╝ ╚══════╝╚═╝╚═╝  ╚═══╝ 's Leetcode Template!
Version 1.0.1.
Recommended standard: C++20. Minimum standard: C++17.
In general, this source code can be found archived here: https://github.com/hellolin-oi/CP-Code/tree/main/LeetCode
The main code section is at the end of this file.
*/
#include <bits/stdc++.h>
// #include "atcoder/all"
#if defined(_WIN64) || defined(__x64_64__) || __WORDSIZE == 64
#define ARCH 64
#else
#define ARCH 32
#endif

namespace hellolin_leet {
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
#define fi first
#define se second
#define ps emplace
#define pb emplace_back
constexpr char newl = '\n';

class Solution {
public:
    int minOperations(vi& nums) {
        int ans = 0, tmp = 0;
        for(auto &i : nums) {
            chmax(tmp, i);
            for(; i; i >>= 1) if(i & 1) ++ans;
        }
        for(; tmp > 1; tmp >>= 1) ++ans;
        // return --ans;
        return ans;
    }
};

} // namespace hellolin_leet

using namespace hellolin_leet;
