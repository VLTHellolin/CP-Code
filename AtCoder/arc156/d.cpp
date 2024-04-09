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
static constexpr int N = 1e4 + 11, M = 998244353, P = 2048;
ll f[60][N * 2], ans, k;
int n, a[N];
void main() {
  f[0][0] = 1;
  read(n, k);
  read_n(a+1, n);
  for(int i=0; i<=53; ++i) {
    if((k >> i) & 1) {
      for(int p=1; p<=n; ++p)
        for(int j=0; j<P; ++j)
          
    } else {
      for(int j=0; j<P; ++j) {
        f[i + 1][j >> 1] ^= f[i][j];
      }
    }
  }
}
} // namespace hellolin