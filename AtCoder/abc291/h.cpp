// Hellolin's Code Template v4.1.1
// *INDENT-OFF*
// NOLINTBEGIN
// clang-format off
#include <bits/stdc++.h>
namespace hellolin {
using ll=long long;using ull=unsigned long long;using lf=double;using llf=long double;
#define _us(x) using std:: x
_us(cin);_us(cout);_us(cerr);_us(endl);_us(swap);_us(sort);_us(unique);_us(reverse);_us(accumulate);_us(lower_bound);_us(upper_bound);_us(max_element);_us(min_element);_us(max);_us(min);
_us(string);_us(array);_us(set);_us(multiset);_us(unordered_set);_us(map);_us(multimap);_us(unordered_map);_us(pair);_us(tuple);_us(queue);_us(stack);_us(bitset);_us(priority_queue);
#undef _us
#define pu push
#define em emplace
#define pb push_back
#define eb emplace_back
#define newl ('\n')
#define sorl(a, b) (" \n"[a==b])
#define fileio(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout)
template<class T,class F>inline bool chmax(T&x,F y){return y>x?x=y,1:0;}template<class T,class F>inline bool chmin(T&x,F y){return y<x?x=y,1:0;}
template<class T>inline T pow(T x,ll y,ll m){T s=1;for(;y;y>>=1,(x*=x)%=m)(y&1)&&((s*=x)%=m);return s;}template<class T>inline T inv(T x,ll m){return pow(x,m-2,m);}
template<class T>inline T pow(T x,ll y){T s=1;for(;y;y>>=1,x*=x)(y&1)&&(s*=x);return s;}
template<class T>struct vector:std::vector<T> {
using std::vector<T>::vector;explicit vector(const std::vector<T>&x):std::vector<T>(x){}
inline void sort(){std::sort(this->begin(),this->end());}template<class F>inline void sort(F f){std::sort(this->begin(),this->end(),f);}
inline void unique(){this->erase(std::unique(this->begin(),this->end()),this->end());}inline void reverse(){std::reverse(this->begin(),this->end());}
template<class F>inline bool every(F f)const{bool r=true;for(const auto&i:*this)r&=f(i);return r;}template<class F>inline bool exist(F f)const{bool r=false;for(const auto&i:*this)r|=f(i);return r;}
inline vector<T> slice(int l,int r)const{if(r>l)return {};if(r<this->size())return vector(this->begin()+l,this->begin()+r);vector a(this->begin()+l,this->end());return a.resize(r-l),a;}
inline friend std::istream& operator>>(std::istream&i,vector<T>&v){for(auto&x:v)i>>x;return i;}inline void from(const string &s){this=vector<T>(s.begin(),s.end());}
inline void fill(int x,int l,int r){std::fill(this->begin()+l,this->begin()+r,x);}inline void fill(int x){this->fill(x,0,this->size());}
template<class F>inline vector<T> filter(F f)const{vector<T>res;for(const auto&i:*this)if(f(i))res.push_back(i);return res;}
template<class F>inline void for_each(F f){for(auto&i:*this)f(i);}inline void concat(const vector<T>&x){this->insert(this->end(),x.begin(),x.end());}
};
template<class T,ll m>struct modint{
T x;modint():x(0){}modint(T _x):x(_x){x%=m,x<0&&(x+=m);}template<class F>operator F(){return x;}inline ll mod(){return m;}
friend inline modint operator+(modint a,modint b){return ((a.x+=b.x)>=m&&(a.x-=m)),a;}friend inline modint operator-(modint a,modint b){return ((a.x-=b.x)<0&&(a.x+=m)),a;}
friend inline modint operator*(modint a,modint b){return a.x*b.x%m;}friend inline modint operator/(modint a,modint b){return a.x*inv(b.x,m)%m;}
friend inline modint operator%(modint a,modint b){return a.x%m;}inline modint&operator%=(modint b){return *this=*this%b;}
inline modint&operator+=(modint b){return *this=*this+b;}inline modint&operator-=(modint b){return *this=*this-b;}
inline modint&operator*=(modint b){return *this=*this*b;}inline modint&operator/=(modint b){return *this=*this/b;}
inline modint&operator++(){return *this+=1;}inline modint&operator++(int){auto a=*this;return *this+=1,a;}
inline modint&operator--(){return *this-=1;}inline modint&operator--(int){auto a=*this;return *this-=1,a;}
inline modint power(T y){return modint<T,m>(pow(x,y,m));}inline modint inverse(){return modint<T,m>(inv(x,m));}
};
template<class...A>inline string format(const string&s,A&&...a)
{int n=snprintf(nullptr,0,s.c_str(),a...);char*b=new char[n+1];snprintf(b,n+1,s.c_str(),a...);string res(b);delete[]b;return res;}
template<class T=int>inline T read(){T x;cin>>x;return x;}template<class T>inline void read(T&x){cin>>x;}template<class T,class...A>inline void read(T&x,A&&...a){cin>>x;read(a...);}
template<class T>inline void write(T x){cout<<x;}template<class T,class...A>inline void write(T x,A...a){cout<<x;write(a...);}template<class...A>inline void writeln(A...a){write(a...,'\n');}
template<class...A>inline void writef(string x,A...a){write(format(x,a...));}template<class...A>inline void writefln(string x,A...a){write(format(x,a...));write('\n');}
template<class T>inline void read_arr(T*x,T*y){while(x!=y)read(*(x++));}template<class T>inline void write_arr(T*x,T*y,char a=' ',char b='\n'){while(x!=y){write(*(x++));write(x==y?b:a);}}
void main();
}
int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    hellolin::main();
}
// NOLINTEND
// clang-format on
#ifndef HELLOLIN_GRAPH_TREE_DIVIDE_HPP
#define HELLOLIN_GRAPH_TREE_DIVIDE_HPP 1
#include <functional>
#include <vector>

namespace hellolin {

class tree_divide_graph {
private:
    int n, rt, ntot;
    std::vector<std::vector<int>> g;
    std::vector<int> fa, sz, val;
    std::vector<bool> vis;

public:
    tree_divide_graph() {}
    explicit tree_divide_graph(int _n)
        : n(_n)
        , g(_n + 1)
        , fa(_n + 1)
        , sz(_n + 1)
        , val(_n + 1)
        , vis(_n + 1) {}
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    const std::vector<int> &build() {
        val[0] = n + 1;
        std::function<void(int, int)> get_root = [&](int u, int f) {
            val[u] = 0;
            sz[u] = 1;
            for (const int &v : g[u]) {
                if (v == f || vis[v]) continue;
                get_root(v, u);
                val[u] = std::max(val[u], sz[v]);
                sz[u] += sz[v];
            }
            val[u] = std::max(val[u], ntot - sz[u]);
            if (val[rt] > val[u]) rt = u;
        };
        std::function<void(int)> dfs = [&](int u) {
            vis[u] = true;
            get_root(u, 0);
            for (const int &v : g[u]) {
                if (vis[v]) continue;
                ntot = sz[v];
                rt = 0;
                get_root(v, u);
                fa[rt] = u;
                dfs(rt);
            }
        };
        ntot = n;
        rt = 0;
        get_root(1, 0);
        fa[rt] = -1;
        dfs(rt);
        return fa;
    }
    int size() const {
        return n;
    }
};

} // namespace hellolin

#endif

namespace hellolin {

int n;
void main() {
    read(n);
    tree_divide_graph g(n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        read(u, v);
        g.add_edge(u, v);
    }
    auto &res = g.build();
    for (int i = 1; i <= n; ++i)
        write(res[i], sorl(i, n));
}
} // namespace hellolin