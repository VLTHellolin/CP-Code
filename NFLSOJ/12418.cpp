// Hellolin's Code Template (with Main function) v4.0.2
// *INDENT-OFF*
// NOLINTBEGIN
// clang-format off
#define HLCTv4 1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
namespace hellolin {
namespace def {
using ll=long long;using ull=unsigned long long;using lf=long double;using llf=long double;
#ifdef __SIZEOF_INT128__
using i128=__int128_t;using u128=__uint128_t;
#else
using i128=ll; using u128=ull;
#endif
#define _us(x) using std:: x
_us(cin);_us(cout);_us(cerr);_us(endl);_us(swap);_us(sort);_us(unique);_us(reverse);_us(accumulate);_us(lower_bound);_us(upper_bound);_us(max_element);_us(min_element);
_us(max);_us(min);_us(array);_us(set);_us(multiset);_us(unordered_set);_us(map);_us(multimap);_us(unordered_map);_us(pair);_us(tuple);_us(queue);_us(stack);_us(bitset);
using __gnu_pbds::priority_queue;
#undef _us
#define ps emplace
#define pb emplace_back
#define newl ('\n')
#define sorl(a, b) (" \n"[a==b])
} using namespace def;
namespace container {
template<class T>struct vector:std::vector<T> {
    using std::vector<T>::vector;explicit vector(const std::vector<T>&x):std::vector<T>(x){}
    inline void sort(){sort(this->begin(),this->end());}template<class F>inline void sort(F f){sort(this->begin(),this->end(),f);}
    inline void unique(){this->erase(unique(this->begin(),this->end()),this->end());}
    template<class F>inline bool every(F f)const{bool r=true;for(const auto&i:*this)r&=f(i);return r;}
    template<class F>inline bool exist(F f)const{bool r=false;for(const auto&i:*this)r|=f(i);return r;}
    inline vector<T> slice(int l,int r)const{
        if(r>l)return {};if(r<this->size())return vector(this->begin()+l,this->begin()+r);vector a(this->begin()+l,this->end());return a.resize(r-l),a;
    }
    inline friend std::istream& operator>>(std::istream&i,vector<T>&v){for(auto&x:v)i>>x;return i;}
};
struct string:std::string {
    using std::string::string;string(const std::string&s):std::string(s){}
    template<class...A>inline string format(A...a)const;
    inline string slice(int l,int r)const{
        if(r>l)return {};if(r<this->size())return string(this->begin()+l,this->begin()+r);string a(this->begin()+l,this->end());return a.resize(r-l),a;
    }
    inline vector<string> split(const string&d)const{
        if(this->empty())return {};char*a=new char[this->size()+1],*b=new char[d.size()+1];strcpy(a,this->c_str()),strcpy(b,d.c_str());
        vector<string>res;for(char*x=strtok(a,b);x;x=strtok(nullptr,b))res.push_back(x);delete[]a;delete[]b;return res;
    }
};
template<class T>inline string to_string(const T&x){return std::to_string(x);}inline string to_string(const string&x){return x;}
inline string to_string(const char*x){return string(x);}inline string to_string(const std::string&x){return string(x);}
inline string operator""_s(ull x){return to_string(x);}inline string operator""_s(llf x){return to_string(x);}
inline string operator""_s(const char*c){return string(c);}inline string operator""_s(const char*c,size_t l){return string(c,l);}
class formatter {
private:
    vector<string>_r;void _pa(){}
    template<class T>void _pa(T x){_r.push_back(to_string(x));}template<class T,class...A>void _pa(T x,A...a){_pa(x),_pa(a...);}
public:
    template<class...A>string operator()(string s,A...a) {
        _r.clear();_pa(a...);string res;vector<int> _b;int _bt=0,_rt=0;
        for(int i=0;i<(int)s.size();++i)if(s[i]=='}')_b.push_back(i);
        for(int i=0;i<(int)s.size();++i)
            switch(s[i]) {
            case '{':res+=(i==_b[_bt]-1)?_r[_rt++]:_r[stoi(s.substr(i+1,_b[_bt]-i-1))-1];i=_b[_bt++];break;
            default:res+=s[i];break;
            }
        return res;
    }
} _fm;template<class...A>inline string string::format(A...a)const{return _fm(*this,a...);}
} using namespace container;
namespace util {
template<class T,class F>inline bool chmax(T&x,F y){return y>x?x=y,1:0;}template<class T,class F>inline bool chmin(T&x,F y){return y<x?x=y,1:0;}
template<class T>inline T pow(T x,ll y,ll m){T s=1;for(;y;y>>=1,(x*=x)%=m)(y&1)&&((s*=x)%=m);return s;}
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
template<class T=int>inline T read(){T x;cin>>x;return x;}template<class T>inline void read(T&x){cin>>x;}
template<class T,class...A>inline void read(T&x,A&&...a){read(x),read(a...);}
template<class...A>inline void write(const string&s,A...a){cout<<s.format(a...);}
template<class...A>inline void writeln(const string&s,A...a){write(s,a...);cout<<'\n';}
} using namespace util;
void main();
}
int main(){std::cin.tie(nullptr)->sync_with_stdio(false);hellolin::main();}
// *INDENT-ON*
// NOLINTEND
// clang-format on
namespace hellolin {
constexpr int N = 2000;
int n;
bool ans;
int a[N], b[N];
vector<pair<int, int>> co;
void mv(int x, int y) {
    while (x != y) {
        if(a[y - 1] < a[y]) {
            ans = false;
            break;
        }
        co.pb(y - 1, y);
        swap(a[y - 1], a[y]);
        --y;
    }
}
void main() {
#ifndef LOCAL
    freopen("subarray.in", "r", stdin);
    freopen("subarray.out", "w", stdout);
#endif
    for (int T = read(); T--;) {
        read(n);
        for (int i = 1; i <= n; ++i)
            read(a[i]);
        for (int i = 1; i <= n; ++i)
            read(b[i]);
        ans = true;
        co.clear();
        for (int i = 1; i <= n; ++i) {
            if (a[i] == b[i]) continue;
            int f = -1;
            for (int j = i; j <= n; ++j) {
                if (a[j] == b[i]) {
                    f = j;
                    break;
                }
            }
            if (f == -1) {
                ans = false;
                break;
            }
            mv(i, f);
            if(ans == false) break;
        }
        if (ans) {
            write("0\n{}\n", co.size());
            for (auto &i : co) {
                writeln("{} {}", i.first, i.second);
            }
        } else
            writeln("-1");
    }
}
} // namespace hellolin