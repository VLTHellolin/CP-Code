// ****************************** //
//    Hellolin's Code Template    //
//             v4.4.0             //
// ****************************** //

// NOLINTBEGIN
// clang-format off
#include <bits/stdc++.h>
#ifdef LOCAL
#include "hellolin/a/debug_tools.hpp"
#endif
using namespace std;namespace hellolin{using ll=long long;using ull=unsigned long long;using cp=complex<double>;mt19937_64 mtrng(chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now().time_since_epoch()).count());template<class T>T rnd(T l,T r){return std::uniform_int_distribution<T>(l,r)(mtrng);}template<class T>bool chmax(T&x,T y){return y>x?x=y,1:0;}template<class T>bool chmin(T&x,T y){return y<x?x=y,1:0;}template<class T>T pow(T x,ll y,T m){T r=1;for(;y;y>>=1,(x*=x)%=m)(y&1)&&((r*=x)%=m);return r;}template<class T>T inv(T x,T m){return pow(x,m-2,m);}template<class T,const T M>struct Z{T x;Z(T y=0){x=y%M,x<0&&(x+=M);}friend Z operator+(Z a,Z b){return((a.x+=b.x)>=M&&(a.x-=M)),a;}friend Z operator-(Z a,Z b){return((a.x-=b.x)<0&&(a.x+=M)),a;}friend Z operator*(Z a,Z b){return a.x*b.x%M;}friend Z operator/(Z a,Z b){return a.x*inv(b.x,M)%M;}Z&operator+=(Z a){return(x+=a.x)>=M&&(x-=M),*this;}Z&operator-=(Z a){return(x-=a.x)<0&&(x+=M),*this;}Z&operator*=(Z a){return x=x*a.x%M,*this;}Z&operator/=(Z a){return x=x*inv(a.x,M)%M,*this;}};template<class T=int>T read(){T x;cin>>x;return x;}template<class T>void read(T&x){cin>>x;}template<class A,class B>void read(pair<A,B>&x){cin>>x.first>>x.second;}template<class T,class...A>void read(T&x,A&&...a){read(x),read(a...);}template<class T>void read_n(T x,int n){while(n--)cin>>*x++;}template<class T>void read_v(T x,T y){while(x!=y)cin>>*x++;}template<class T>void print(T x){cout<<x;}template<class T,class...A>void print(T x,A...a){print(x),print(a...);}template<class...A>void println(A...a){print(a...),print('\n');}template<class T>void println_n(T x,int n){while(n--)cout<<*x++<<" \n"[!n];}template<class T>void println_v(T x,T y){while(x!=y)cout<<*x++<<" \n"[x==y];}template<class...A>void print_f(const char*f,A...a){char*t=new char[snprintf(nullptr,0,f,a...)+1];sprintf(t,f,a...);cout<<t;delete[]t;}void main();}
int main() {
  // freopen(".in", "r", stdin);
  // freopen(".out", "w", stdout);
  cin.tie(nullptr)->sync_with_stdio(false);
  hellolin::main();
}
// NOLINTEND
// clang-format on

namespace hellolin {
static constexpr int M = 2e5;
static constexpr ll Mod = 998244353;
ll fc[M + 5];
unordered_map<ll, ll> mp;
ll dfs(ll n) {
  if (n <= M) return fc[n];
  if (mp.find(n) != mp.end()) return mp[n];

  ll ans = 1, l = 2, r;

  for (; l <= n; l = r + 1)
    (ans += dfs(n / l) * ((r = n / (n / l)) - l + 1)) %= Mod;

  return mp[n] = ans;
}
void main() {
  fc[1] = 1;
  for (int i = 1; i <= M; ++i)
    for (int j = i << 1; j <= M; j += i)
      (fc[j] += fc[i]) %= Mod;

  for (int i = 2; i <= M; ++i)
    (fc[i] += fc[i - 1]) %= Mod;

  ll n;
  read(n);
  println(dfs(n));
}
} // namespace hellolin