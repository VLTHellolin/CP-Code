/**
 * @file Hellolin's Code Template
 * @version 4.3.1
 */
// *INDENT-OFF*
// NOLINTBEGIN
// clang-format off
#include <bits/stdc++.h>
#ifdef LOCAL
#include "hellolin/a/debug_tools.hpp"
#endif
using namespace std;
namespace hellolin {
using ll = long long; using ull = unsigned long long; using cp = complex<double>;
#define rangeOf(x) x.begin(), x.end()
class hellolinUtility {
mt19937 _m_r;
public:hellolinUtility():_m_r(chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now().time_since_epoch()).count()){};template<class T>T random(T l,T r){uniform_int_distribution<T>d(l, r);return d(_m_r);}
template<class T,class F>bool chmax(T&x,F y){return y>x?x=y,1:0;}template<class T,class F>bool chmin(T&x,F y){return y<x?x=y,1:0;}template<class T>T pow(T x,ll y,ll m){T s=1;for(;y;y>>=1,(x*=x)%=m)(y&1)&&((s*=x)%=m);return s;}template<class T>T inv(T x,ll m){return pow(x,m-2,m);}template<class T>T pow(T x,ll y){T s=1;for(;y;y>>=1,x*=x)(y&1)&&(s*=x);return s;}
template<class T=int>T reads(istream&i){T x;i>>x;return x;}template<class T>void reads(istream&i,T&x){i>>x;}template<class T,class...A>void reads(istream&i,T&x,A&&...y){i>>x;reads(i,y...);}template<class T=int>T read(){return reads<T>(cin);}template<class...A>void read(A&&...x){reads(cin,x...);}template<class T>void writes(ostream&o,T x){o<<x;}template<class T,class...A>void writes(ostream&o,const T&x,A...y){o<<x;writes(o,y...);}template<class...A>void writesln(ostream&o,A...x){writes(o,x...,'\n');}template<class...A>void write(A...x){writes(cout,x...);}template<class...A>void writeln(A...x){writesln(cout,x...);}template<class T>void reads_arr(istream&i,T x,T y){while(x!=y)reads(i,*(x++));}template<class T>void writes_arr(ostream&o,T x,T y,char a=' ',char b='\n'){while(x!=y){writes(o,*(x++));writes(o,x==y?b:a);}}template<class T>void read_arr(T x,T y){reads_arr(cin,x,y);}template<class T>void write_arr(T x,T y,char a=' ',char b='\n'){writes_arr(cout,x,y,a,b);}
} util;
template<class T,ll m> struct modInt {
T x;modInt():x(0){}modInt(T _x):x(_x){x%=m,x<0&&(x+=m);}friend istream&operator>>(istream&i,modInt&x){return i>>x.x;}friend ostream& operator<<(ostream&o,const modInt&x){return o<<x.x;}template<class F>operator F(){return x;}ll mod(){return m;}friend modInt operator+(modInt a,modInt b){return((a.x+=b.x)>=m&&(a.x-=m)),a;}friend modInt operator-(modInt a,modInt b){return((a.x-=b.x)<0&&(a.x+=m)),a;}friend modInt operator*(modInt a,modInt b){return a.x*b.x%m;}friend modInt operator/(modInt a,modInt b){return a.x*util.inv(b.x,m)%m;}friend modInt operator%(modInt a,modInt b){return a.x%m;}modInt&operator%=(modInt b){return*this=*this%b;}modInt&operator+=(modInt b){return*this=*this+b;}modInt&operator-=(modInt b){return*this=*this-b;}modInt&operator*=(modInt b){return*this=*this*b;}modInt&operator/=(modInt b){return*this=*this/b;}modInt&operator++(){return*this+=1;}modInt&operator++(int){auto a=*this;return*this+=1,a;}modInt&operator--(){return*this-=1;}modInt&operator--(int){auto a=*this;return*this-=1,a;}modInt pow(T y){return modInt<T,m>(util.pow(x,y,m));}modInt inv(){return modInt<T,m>(util.inv(x,m));}
};
void main();
} // namespace hellolin
int main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    cin.tie(nullptr)->sync_with_stdio(false);
    hellolin::main();
}
// NOLINTEND
// clang-format on

namespace hellolin {
constexpr int N = 1e5 + 10, Inf = 7e8;
class dsu {
private:
    vector<int> f;

public:
    explicit dsu(int _n)
        : f(_n) {
        for (int i = 0; i < _n; ++i)
            f[i] = i;
    }
    int find(int x) {
        return f[x] == x ? x : f[x] = find(f[x]);
    }
    void merge(int x, int y) {
        f[find(x)] = find(y);
    }
};
bool chk(int x) {
    auto s = to_string(x);
    for (const auto &i : s)
        if (i != '4' && i != '7') return false;
    return true;
}
int n, m, ans;
int buc[N], rbuc[N], f[N];
void main() {
    util.read(n, m);
    dsu d(n + 1);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        util.read(u, v);
        d.merge(u, v);
    }
    for (int i = 1; i <= n; ++i)
        ++buc[d.find(i)];
    for (int i = 1; i <= n; ++i)
        ++rbuc[buc[i]];
    fill(&f[1], &f[n + 5], Inf);
    for (int i = 1; i <= n; ++i) {
        int val = rbuc[i], bin = 1;
        while (val > 0) {
            int now = min(val, bin);
            val -= bin;
            bin <<= 1;
            for (int j = n - i * now; ~j; --j)
                util.chmin(f[j + i * now], f[j] + now);
        }
    }
    ans = Inf;
    for (int i = 1; i <= n; ++i) {
        if (chk(i)) util.chmin(ans, f[i]);
    }
    util.writeln(ans == Inf ? -1 : --ans);
}
} // namespace hellolin