// Hellolin's Code Template (with Main function) v4.0.0
// *INDENT-OFF*
// NOLINTBEGIN
// clang-format off
#define HLCTv4 1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
namespace hellolin {
namespace def {
using i8 = signed char; using u8 = unsigned char; using i16 = short; using u16 = unsigned short;
using i64 = long long; using u64 = unsigned long long; using f32 = float; using f64 = long double; using f96 = long double;
#ifdef __SIZEOF_INT128__
using i128 = __int128_t; using u128 = __uint128_t;
#else
using i128 = i64; using u128 = u64;
#endif
#define _us(x) using std:: x
_us(cin);_us(cout);_us(cerr);_us(endl);_us(swap);_us(sort);_us(unique);_us(reverse);_us(accumulate);
_us(lower_bound);_us(upper_bound);_us(max_element);_us(min_element);_us(max);_us(min);
_us(array);_us(set);_us(multiset);_us(unordered_set);_us(map);_us(multimap);_us(unordered_map);
_us(pair);_us(tuple);_us(queue);_us(stack);_us(bitset);using __gnu_pbds::priority_queue;
#undef _us
#define ps emplace
#define pb emplace_back
#define newl ('\n')
#define sorl(a, b) (" \n"[a==b])
} using namespace def;
namespace container {
template<class T>struct vector : std::vector<T> {
    using std::vector<T>::vector;
    explicit vector(const std::vector<T>&x):std::vector<T>(x){}
    inline void sort(){sort(this->begin(),this->end());}
    template<class F>inline void sort(F f){sort(this->begin(),this->end(),f);}
    inline void unique(){this->erase(unique(this->begin(),this->end()),this->end());}
    template<class F>inline bool every(F f)const{bool r = true;for(const auto&i:*this)r&=f(i);return r;}
    template<class F>inline bool exist(F f)const{bool r = false;for(const auto&i:*this)r|=f(i);return r;}
    inline vector<T> slice(int l, int r)const{
        if(r>l)return {};
        if(r<this->size())return vector(this->begin()+l,this->begin()+r);
        vector a(this->begin()+l,this->end());return a.resize(r-l),a;
    }
};
struct string : std::string {
    using std::string::string;
    string(const std::string&s):std::string(s){}
    template<class...A>inline string format(A...a)const;
    inline string slice(int l, int r)const{
        if(r>l)return {};
        if(r<this->size())return string(this->begin()+l,this->begin()+r);
        string a(this->begin()+l,this->end());return a.resize(r-l),a;
    }
};
template<class T>inline string to_string(const T&x){return std::to_string(x);}
inline string to_string(const char*x){return string(x);}
inline string to_string(const std::string&x){return string(x);}
inline string operator""_s(u64 x){return to_string(x);}
inline string operator""_s(f64 x){return to_string(x);}
inline string operator""_s(const char*c){return string(c);}
inline string operator""_s(const char*c,size_t l){return string(c, l);}
class formatter {
private:
    vector<string>_r;
    template<class T>void _pa(T x){_r.push_back(to_string(x));}
    template<class T,class...A>void _pa(T x,A...a){_pa(x),_pa(a...);}
public:
    template<class...A>string operator()(string s,A...a) {
        _r.clear();_pa(a...);string res;vector<int> _b;int _bt=0,_rt=0;
        for(int i=0;i<(int)s.size();++i)if(s[i]=='}')_b.push_back(i);
        for(int i=0;i<(int)s.size();++i)
            switch(s[i]) {
            case '{':
                if(i==_b[_bt]-1)res+=_r[_rt++];else res+=_r[stoi(s.substr(i+1,_b[_bt]-i-1))-1];
                i=_b[_bt];++_bt;break;
            default:res+=s[i];break;
            }
        return res;
    }
} _fm;
template<class...A>inline string string::format(A...a)const{return _fm(*this,a...);}
} using namespace container;
namespace util {
template<class T,class U>inline bool chmax(T&x,U y){return y>x?x=y,1:0;}
template<class T,class U>inline bool chmin(T&x,U y){return y<x?x=y,1:0;}
template<class T=int>inline T read(){T x;cin>>x;return x;}
template<class...A>inline void write(const string&s,A...a){cout<<s.format(a...);}
template<class...A>inline void writeln(const string&s,A...a){write(s+'\n',a...);}
template<class...A>inline void log(const string&s,A...a){cerr<<s.format(a...);}
template<class...A>inline void logln(const string&s,A...a){log(s+'\n',a...);}
} using namespace util;
void main();
}
int main(){std::cin.tie(nullptr)->sync_with_stdio(false);hellolin::main();}
// *INDENT-ON*
// NOLINTEND
// clang-format on
#ifndef HELLOLIN_DISTRIBUTION_HPP
#define HELLOLIN_DISTRIBUTION_HPP 1
#include <algorithm>
#include <vector>

namespace hellolin {

template <class T>
class distribution {
private:
    bool ready;
    std::vector<T> d;
    void init() {
        std::sort(d.begin(), d.end());
        d.erase(std::unique(d.begin(), d.end()), d.end());
        ready = 1;
    }

public:
    explicit distribution()
        : ready(0) {}
    void push(T x) {
        d.emplace_back(x);
        ready = 0;
    }
    template <class... Args>
    void push(T x, Args... y) {
        push(x);
        push(y...);
    }
    int distribute(T x) {
        if (!ready) init();
        return std::lower_bound(d.begin(), d.end(), x) - d.begin() + 1;
    }
    T tribute(int x) {
        if (!ready) init();
        return d[x - 1];
    }
    int size() {
        if (!ready) init();
        return d.size();
    }
    void clear() {
        d.clear();
    }
};

} // namespace hellolin

#endif
namespace hellolin {
constexpr int N = 1e5 + 11;
constexpr i64 Mod = 1e9 + 7;
i64 ans, now;
int fn[N];
int n, k;
string s;
// int cti(char c) {
//     if (islower(c)) return c - 'a';
//     return c - 'A' + 26;
// }
struct pf {
    int x[60];
    bool operator<(const pf &t) const {
        for (int i = 0; i < k; ++i) {
            if (x[i] == t.x[i]) continue;
            return x[i] < t.x[i];
        }
        return false;
    }
} q[N];
distribution<char> di;
struct my_cmp {
    bool operator()(const int &a, const int &b) const { return q[a] < q[b]; }
};
map<int, int, my_cmp> mp;
void main() {
#ifndef LOCAL
    freopen("magic.in", "r", stdin);
    freopen("magic.out", "w", stdout);
#endif
    cin >> n >> s;
    s = '#' + s;
    for (int i = 1; i <= n; ++i)
        di.push(s[i]);
    for (int i = 1; i <= n; ++i)
        fn[i] = di.distribute(s[i]) - 1;
    k = di.size();
    mp[0] = 1;
    for (int i = 1; i <= n; ++i) {
        q[i].x[0] = q[i - 1].x[0];
        for (int j = 1; j < k; ++j)
            q[i].x[j] = q[i - 1].x[j];
        if (fn[i]) {
            ++q[i].x[fn[i]];
        } else
            for (int j = 1; j < k; ++j)
                --q[i].x[j];
        now = mp[i];
        (ans += now++) %= Mod;
        mp[i] = now;
    }
    cout << ans % Mod << newl;
}
} // namespace hellolin