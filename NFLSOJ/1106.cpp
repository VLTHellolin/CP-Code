#include <cstdio>
using i64 = long long;
using u64 = unsigned long long;
#ifdef _WIN32
#define outi64 "%I64d\n"
#else
#define outi64 "%lld\n"
#endif
constexpr int N = 2e5 + 5;
int rn, n, q, dl;
int a[N];
int tr[2][N / 2 + 1];
i64 ans;
void chn(int num, int p, int w) {
    for (; p <= n; p += p & -p)
        tr[num][p] ^= w;
}
i64 sum(int num, int l, int r) {
    i64 al = 0, ar = 0;
    for (; l; l -= l & -l)
        al ^= tr[num][l];
    for (; r; r -= r & -r)
        ar ^= tr[num][r];
    return ar ^ al;
}
#define wt(x) (x & 1)
#define wn(x) (x / 2 + ((x & 1) ? 1 : 0))
int main() {
#ifndef LOCAL
    freopen("orange.in", "r", stdin);
    freopen("orange.out", "w", stdout);
#endif
    scanf("%d%d", &rn, &q);
    n = rn / 2 + 1;
    for (int i = 1; i <= rn; ++i) {
        int x;
        scanf("%d", &x);
        a[i] = x;
        chn(wt(i), wn(i), x);
    }
    while (q--) {
        int op, x, y;
        scanf("%d%d%d", &op, &x, &y);
        if (op == 1) {
            chn(wt(x), wn(x), a[x] ^ y);
            a[x] = y;
        } else {
            ans = 0;
            if ((y - x + 1) & 1) {
                ans = sum(wt(x), wn(x) - 1, wn(y));
            }
            printf(outi64, ans);
        }
    }

    return 0;
}