// Hellolin's Code Template (LeetCode) v4.0.2
// *INDENT-OFF*
// NOLINTBEGIN
// clang-format off
#define HLCTv4 1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
namespace hellolin {
using namespace std;
namespace util {
using ll=long long;using ull=unsigned long long;
template<class T,class F>inline bool chmax(T&x,F y){return y>x?x=y,1:0;}template<class T,class F>inline bool chmin(T&x,F y){return y<x?x=y,1:0;}
template<class T>inline T pow(T x,ll y,ll m){T s=1;for(;y;y>>=1,(x*=x)%=m)(y&1)&&(s*=x)%=m;return s;}
template<class T>inline T inv(T x,ll m){return pow(x,m-2,m);}
template<class T,ll m>struct modint{
    T x;modint():x(0){}modint(T _x):x(_x){x%=m,x<0&&(x+=m);}
    template<class F>operator F(){return x;}inline ll mod(){return m;}
    friend inline modint operator+(modint a,modint b){return ((a.x+=b.x)>=m&&(a.x-=m)),a;}
    friend inline modint operator-(modint a,modint b){return ((a.x-=b.x)<0&&(a.x+=m)),a;}
    friend inline modint operator*(modint a,modint b){return a.x*b.x%m;}friend inline modint operator/(modint a,modint b){return a.x*inv(b.x,m)%m;}
    friend inline modint operator%(modint a,modint b){return a.x%m;}inline modint&operator%=(modint b){return *this=*this%b;}
    inline modint&operator+=(modint b){return *this=*this+b;}inline modint&operator-=(modint b){return *this=*this-b;}
    inline modint&operator*=(modint b){return *this=*this*b;}inline modint&operator/=(modint b){return *this=*this/b;}
    inline modint&operator++(){return *this+=1;}inline modint&operator++(int){auto a=*this;return *this+=1,a;}
    inline modint&operator--(){return *this-=1;}inline modint&operator--(int){auto a=*this;return *this-=1,a;}
};
} using namespace util;
// *INDENT-ON*
// NOLINTEND
// clang-format on

class Solution {
private:
    vector<string> res;
    void dfs(int n, string w, int a, int b) {
        if ((int) w.size() == n * 2) {
            res.push_back(w);
            return;
        }
        if (a < n)
            dfs(n, w + '(', a + 1, b);
        if (b < a)
            dfs(n, w + ')', a, b + 1);
    }

public:
    vector<string> generateParenthesis(int n) {
        dfs(n, "", 0, 0);
        return res;
    }
};

} // namespace hellolin

using namespace hellolin;