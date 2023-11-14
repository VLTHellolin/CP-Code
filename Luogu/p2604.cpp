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
#ifndef HELLOLIN_GRAPH_MIN_COST_FLOW_HPP
#define HELLOLIN_GRAPH_MIN_COST_FLOW_HPP 1
#include <algorithm>
#include <limits>
#include <queue>
#include <vector>

namespace hellolin {

namespace graph {

template <class T, class H>
class min_cost_flow {
private:
    int n, m;
    long long inf;
    std::vector<std::pair<int, int>> pr;
    class internal_edge {
    public:
        int to, p;
        T w;
        H cost;
    };
    std::vector<std::vector<internal_edge>> g;
    std::vector<bool> vis;
    class spfa_node {
    public:
        T flow;
        H dis;
        std::pair<int, int> p;
    };
    std::vector<spfa_node> s;
    T flow_res;
    H cost_res;
    std::queue<int> q;

    bool spfa(int fr, int to) {
        for (int i = 1; i <= n; i++) {
            s[i].dis = inf;
        }
        vis.clear();
        vis[fr] = 1;
        q = std::queue<int>();
        q.push(fr);
        s[fr].dis = 0;
        s[fr].flow = inf;
        while (q.size()) {
            int tp = q.front();
            q.pop();
            vis[tp] = 0;
            int ind = -1;
            for (internal_edge &i : g[tp]) {
                ++ind;
                if (i.w > 0 && i.cost + s[tp].dis < s[i.to].dis) {
                    s[i.to].dis = i.cost + s[tp].dis;
                    s[i.to].flow = std::min(s[tp].flow, i.w);
                    s[i.to].p = {tp, ind};
                    if (!vis[i.to]) {
                        vis[i.to] = 1;
                        q.push(i.to);
                    }
                }
            }
        }
        return s[to].dis != inf;
    }
    void _upd(int fr, int to) {
        int tp1 = to, tp2 = -1, tp3 = -1;
        while (tp1 != fr) {
            tp2 = s[tp1].p.first;
            tp3 = s[tp1].p.second;
            g[tp2][tp3].w -= s[to].flow;
            g[tp1][g[tp2][tp3].p].w += s[to].flow;
            tp1 = tp2;
        }
        flow_res += s[to].flow;
        cost_res += s[to].flow * s[to].dis;
    }

public:
    class edge {
    public:
        int fr, to;
        T w, flow;
        H cost;
    };
    explicit min_cost_flow(int _n, long long _inf = 1e9)
        : n(_n)
        , inf(_inf) {
        g.resize(n + 1);
        vis.resize(n + 1);
        s.resize(n + 1);
    }
    void add_edge(int fr, int to, T w, H co) {
        m = pr.size();
        int _fr = g[fr].size(), _to = g[to].size();
        if (fr == to) ++_to;
        pr.push_back({fr, _fr});
        g[fr].push_back(internal_edge{to, _to, w, co});
        g[to].push_back(internal_edge{fr, _fr, 0, -co});
    }
    edge get_edge(int x) {
        m = pr.size();
        internal_edge e1, e2;
        e1 = g[pr[x].first][pr[x].second];
        e2 = g[e1.to][e1.p];
        return edge{pr[x].first, e1.to, e1.w + e2.w, e2.w, e1.cost + e2.cost};
    }
    std::vector<edge> get_edges() {
        m = pr.size();
        std::vector<edge> e;
        for (int i = 0; i < m; i++) {
            e.push_back(get_edge(i));
        }
        return e;
    }
    std::pair<T, H> get_flow_cost(int fr, int to, T flow_lim = std::numeric_limits<T>::max(), H cost_lim = std::numeric_limits<H>::max()) {
        flow_res = cost_res = 0;
        while (spfa(fr, to) && flow_res < flow_lim && cost_res < cost_lim)
            _upd(fr, to);
        return {flow_res, cost_res};
    }
};

} // namespace graph

} // namespace hellolin

#endif
namespace hellolin {
constexpr int Inf = 1e9 + 1;
int n, m, k, s, t;
void main() {
    read(n, m, k);
    graph::min_cost_flow<int, int> mcf(n);
    s = 1, t = n;
    vector<int> u(m), v(m), w(m), c(m);
    for (int i = 0; i < m; ++i)
        read(u[i], v[i], w[i], c[i]);
    for (int i = 0; i < m; ++i)
        mcf.add_edge(u[i], v[i], w[i], 0);
    write(mcf.get_flow_cost(s, t).first, ' ');
    s = 0, t = n;
    for (int i = 0; i < m; ++i)
        mcf.add_edge(u[i], v[i], Inf, c[i]);
    mcf.add_edge(s, 1, k, 0);
    writeln(mcf.get_flow_cost(s, t).second);
}
} // namespace hellolin