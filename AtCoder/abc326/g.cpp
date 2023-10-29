#include <bits/stdc++.h>
#include "atcoder/all"
constexpr int N = 60;
constexpr long long Inf = 1e12;
int n, m, s, t;
long long c[N], a[N], l[N][N];
int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        std::cin >> c[i];
    for (int i = 1; i <= m; ++i)
        std::cin >> a[i];
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            std::cin >> l[i][j];
    atcoder::mf_graph<long long> mf(5 * (n + 1) + m + 6);
    s = 0, t = 5 * (n + 1) + m + 1;
    for (int i = 1; i <= n; ++i) {
        mf.add_edge(s, 5 * i + 1, Inf);
        for (int j = 1; j <= 4; ++j) {
            mf.add_edge(5 * i + j, 5 * i + j + 1, c[i] * (j - 1));
        }
        mf.add_edge(5 * i + 5, t, c[i] * 4);
    }
    for (int i = 1; i <= m; ++i) {
        mf.add_edge(s, 5 * (n + 1) + i, a[i]);
        for (int j = 1; j <= n; ++j) {
            mf.add_edge(5 * (n + 1) + i, 5 * j + l[i][j], Inf);
        }
    }
    std::cout << std::accumulate(&a[1], &a[m + 1], 0ll) - mf.flow(s, t) << '\n';
}