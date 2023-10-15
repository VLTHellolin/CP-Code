// Hellolin's Code Template (LeetCode) v4.0.0
// *INDENT-OFF*
// NOLINTBEGIN
// clang-format off
#define HLCTv4 1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
namespace hellolin {
using namespace std;
namespace def {
using i8 = signed char; using u8 = unsigned char; using i16 = short; using u16 = unsigned short;
using i64 = long long; using u64 = unsigned long long; using f32 = float; using f64 = long double; using f96 = long double;
#ifdef __SIZEOF_INT128__
using i128 = __int128_t; using u128 = __uint128_t;
#else
using i128 = i64; using u128 = u64;
#endif
#define ps emplace
#define pb emplace_back
#define newl ('\n')
#define sorl(a, b) (" \n"[a==b])
} using namespace def;
namespace util {
template<class T,class U>inline bool chmax(T&x,U y){return y>x?x=y,1:0;}
template<class T,class U>inline bool chmin(T&x,U y){return y<x?x=y,1:0;}
} using namespace util;
// *INDENT-ON*
// NOLINTEND
// clang-format on

class Solution {
public:
    int singleNumber(vector<int> &a) {
        int x = 0, y = 0;
        for (auto &i : a) {
            x = ~y & (i ^ x);
            y = ~x & (i ^ y);
        }
        return x;
    }
};

} // namespace hellolin

using namespace hellolin;