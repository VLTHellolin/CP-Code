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
// #ifndef LOCAL
//     fileio("eliminate");
// #endif
    std::cin.tie(nullptr)->sync_with_stdio(false);
    hellolin::main();
}
// NOLINTEND
// clang-format on
namespace hellolin {
namespace chess {
constexpr int N = 1e5 + 2, SN = 1e5 + 5;
int row, column, n, m, ans;
queue<int> q;
class hellolin_exception : std::exception {
private:
    std::string err;

public:
    hellolin_exception(const std::string &_err)
        : err(_err) {}
    virtual const char *what() const noexcept override {
        return err.c_str();
    }
};
struct coordinate {
    pair<int, int> a, b, c, d;
} coor[SN];
struct controller {
    pair<int, int> x;
    pair<char, char> d;
} cont[SN];
vector<controller> result;
set<pair<int, int>> row_set[SN], column_set[SN];
bool exi[SN];
// UD, LR, UL, UR, DL, DR
vector<pair<char, char>> directions{{'U', 'D'}, {'L', 'R'}, {'U', 'L'}, {'U', 'R'}, {'D', 'L'}, {'D', 'R'}};
vector<char> single_directions{'U', 'D', 'L', 'R'};
pair<int, int> get(char d, int x, int y) {
    switch (d) {
    case 'U':
        return *--column_set[y].lower_bound({x, 0});
        break;
    case 'D':
        return *column_set[y].upper_bound({x, N});
        break;
    case 'L':
        return *--row_set[x].lower_bound({y, 0});
        break;
    case 'R':
        return *row_set[x].upper_bound({y, N});
        break;
    default:
        throw hellolin_exception("The given direction is wrong");
    };
    return {-1, -1};
}
void erase(char d, int x, int y, pair<int, int> r) {
    // cerr << format("%c, %d, %d, {%d %d}\n", d, x, y, r.first, r.second);
    if (d == 'U' || d == 'D') {
        column_set[y].erase(r);
        row_set[r.first].erase({y, r.second});
    } else if (d == 'L' || d == 'R') {
        row_set[x].erase(r);
        column_set[r.first].erase({x, r.second});
    } else {
        throw hellolin_exception("The given direction is wrong");
    }
}
void add(int p, int x, int y) {
    if (row_set[x].lower_bound({y, 0})->first == y) return;
    pair<int, int> fx, fy;
    for (auto &[a, b] : directions) {
        fx = get(a, x, y);
        fy = get(b, x, y);
        if (fx.second && fx.second == fy.second && fy.second == p && !exi[p]) {
            exi[p] = true;
            q.push(p);
            erase(a, x, y, fx);
            erase(b, x, y, fy);
            result.pb({{x, y}, {a, b}});
            return;
        }
    }
}
void ins(int p) {
    auto &[a, b, c, d] = coor[p];
    if (a.first == c.first) {
        add(p, a.first, (b.first + d.first) / 2);
        return;
    }
    if (b.first == d.first) {
        add(p, (a.first + c.first) / 2, b.first);
        return;
    }
    add(p, a.first, d.first);
    add(p, c.first, b.first);
}
void chk(int x, int y) {
    pair<int, int> f;
    for (auto &d : single_directions) {
        f = get(d, x, y);
        if (f.second)
            ins(f.second);
    }
}
void init() {
    read(row, column, n);
    for (int i = 1; i <= n; ++i) {
        auto &[a, b, c, d] = coor[i];
        read(a.first, b.first, c.first, d.first);
        a.second = b.second = c.second = d.second = i;
    }
    read(m);
    for (int i = 1; i <= m; ++i) {
        auto &[x, d] = cont[i];
        read(x.first, x.second, d.first, d.second);
    }
}
void reset() {
    for (int i = 0; i <= row; ++i) {
        row_set[i].clear();
        row_set[i].insert({0, 0});
        row_set[i].insert({N, 0});
    }
    for (int i = 0; i <= column; ++i) {
        column_set[i].clear();
        column_set[i].insert({0, 0});
        column_set[i].insert({N, 0});
    }
    for (int i = 1; i <= n; ++i) {
        auto &[a, b, c, d] = coor[i];
        row_set[a.first].insert(b);
        row_set[c.first].insert(d);
        column_set[b.first].insert(a);
        column_set[d.first].insert(c);
    }
}
void solve_1() {
    pair<int, int> fx = {0, 0}, fy = {0, 0};
    for (int i = 1; i <= m; ++i) {
        auto &[x, d] = cont[i];
        if (row_set[x.first].lower_bound({x.second, 0})->first == x.second) continue;
        fx = get(d.first, x.first, x.second);
        fy = get(d.second, x.first, x.second);
        if (fx.second && fx.second == fy.second) {
            ++ans;
            erase(d.first, x.first, x.second, fx);
            erase(d.second, x.first, x.second, fy);
        }
    }
    // writeln(ans);
    write(ans, ' ');
}
void solve_2() {
    result.clear();
    for (int i = 1; i <= n; ++i) {
        ins(i);
    }
    while (q.size()) {
        int i = q.front();
        q.pop();
        auto &[a, b, c, d] = coor[i];
        chk(a.first, b.first);
        chk(c.first, d.first);
    }
    writeln(result.size());
    // for (auto &[x, d] : result) {
    //     writeln(x.first, ' ', x.second, ' ', d.first, ' ', d.second);
    // }
}
void main() {
    init();
    reset();
    solve_1();
    reset();
    solve_2();
}
} // namespace chess
void main() {
    chess::main();
}
} // namespace hellolin