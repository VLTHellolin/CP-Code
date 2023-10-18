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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode()
        : val(0)
        , left(nullptr)
        , right(nullptr) {}
    TreeNode(int x)
        : val(x)
        , left(nullptr)
        , right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x)
        , left(left)
        , right(right) {}
};
class Solution {
public:
    vector<int> rightSideView(TreeNode *rt) {
        if (!rt) return {};
        unordered_map<int, int> mp;
        int tp = 0;
        queue<pair<TreeNode *, int>> q;
        vector<int> res;
        q.emplace(rt, 0);
        while (q.size()) {
            auto [x, y] = q.front();
            q.pop();
            if (x) {
                chmax(tp, y);
                mp[y] = x->val;
                q.emplace(x->left, y + 1);
                q.emplace(x->right, y + 1);
            }
        }
        for (int i = 0; i <= tp; ++i)
            res.push_back(mp[i]);
        return res;
    }
};

} // namespace hellolin

using namespace hellolin;