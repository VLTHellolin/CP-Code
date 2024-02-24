#include <bits/stdc++.h>
using namespace std;
namespace hellolin {
static constexpr __int16_t N = 501, LK = 30;
static constexpr __int32_t Base = 13331, Mod = 998244353;
__int16_t n, m;
__int32_t k;
__int8_t a[N][N];
static __int64_t p, q;
static constexpr __int8_t dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1}, dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
static __uint32_t bi[LK], ha[N][N][8][LK], curr;
static map<__uint32_t, __int32_t> mp;
static __int16_t i, j, d, w, x, y;
static __int64_t temp;
void main() {
  cin >> n >> m >> k, q = 64ll * n * m * n * m, *bi = Base;
  for (i = 1; i < LK; ++i)
    bi[i] = bi[i - 1] * bi[i - 1];
  for (i = 0; i < n; ++i)
    for (j = 0; j < m; ++j) {
      cin >> a[i][j];
      for (d = 0; d < 8; ++d)
        ha[i][j][d][0] = a[i][j] - 'a';
    }
  for (w = 0; w < LK - 1; ++w)
    for (i = 0; i < n; ++i)
      for (j = 0; j < m; ++j)
        for (d = 0; d < 8; ++d)
          x = (((1 << w) * dx[d] + i) % n + n) % n, y = (((1 << w) * dy[d] + j) % m + m) % m, ha[i][j][d][w + 1] = bi[w] * ha[i][j][d][w] + ha[x][y][d][w];
  for (i = 0; i < n; ++i)
    for (j = 0; j < m; ++j)
      for (d = 0; d < 8; ++d) {
        x = i, y = j, curr = 0;
        for (int w = LK - 1; w >= 0; --w) {
          if ((k >> w & 1) == 0) continue;
          curr = curr * bi[w] + ha[x][y][d][w];
          x = (((1 << w) * dx[d] + x) % n + n) % n, y = (((1 << w) * dy[d] + y) % m + m) % m;
        }
        temp = ++mp[curr], p += temp * temp, p -= (temp - 1) * (temp - 1);
      }
  temp = gcd(p, q), p /= temp, q /= temp, cout << p << '/' << q << '\n';
}
} // namespace hellolin
int main() { hellolin::main(); }