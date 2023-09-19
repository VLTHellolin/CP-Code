// TODO: Fix this.

#ifndef HELLOLIN_GRAPH_KM_ALGO_HPP
#define HELLOLIN_GRAPH_KM_ALGO_HPP 1
#include <algorithm>
#include <limits>
#include <queue>
#include <vector>

namespace hellolin {

namespace graph {

// a.k.a. Hungarian Algorithm (匈牙利算法)
template <class T>
class km_algo {
private:
    int n, m;
    T INF, NINF;
    std::vector<std::vector<T>> g;
    std::vector<T> tl, tr, slack;
    std::vector<bool> vis;
    std::vector<T> z, f;

    void work(int w) {
        int x = 0, y = 0, fy = 0;
        f[y] = w;
        z.clear();
        std::fill(slack.begin(), slack.end(), INF);
        do {
            x = f[y];
            vis[y] = 1;
            T qwq = INF;
            for (int i = 1; i <= n; i++)
                if (!vis[i]) {
                    T tp = tl[x] + tr[i] - g[x][i];
                    if (slack[i] > tp) {
                        slack[i] = tp;
                        z[i] = y;
                    }
                    if (slack[i] < qwq) {
                        qwq = slack[i];
                        fy = i;
                    }
                }
            for (int i = 0; i <= n; i++) {
                if (vis[i]) {
                    tl[f[i]] -= qwq;
                    tr[i] += qwq;
                } else
                    slack[i] -= qwq;
            }
            y = fy;
        } while (f[y]);
        for (; y; y = z[y])
            f[y] = f[z[y]];
    }
    T _query() {
        for (int i = 1; i <= n; i++) {
            tl[i] = NINF;
            tl[i] = std::max(tl[i], *std::max_element(g[i].begin(), g[i].end()));
        }
        for (int i = 1; i <= n; i++) {
            vis.clear();
            work(i);
        }
        T tot = 0;
        for (int i = 1; i <= n; i++)
            tot += g[f[i]][i];
        return tot;
    }

public:
    explicit km_algo(int _n, int _m)
        : n(_n)
        , m(_m)
        , INF(std::numeric_limits<T>::max())
        , NINF(std::numeric_limits<T>::min()) {
        g = std::vector<std::vector<T>>(n + 1, std::vector<T>(n + 1, NINF));
        tl.resize(n + 1, 0);
        tr.resize(n + 1, 0);
        slack.resize(n + 1, 0);
        vis.resize(n + 1, 0);
        z.resize(n + 1, 0);
        f.resize(n + 1, 0);
    }
    void add_edge(int u, int v, T w) {
        g[u][v] = std::max(g[u][v], w);
    }
    std::pair<int, std::vector<T>> query() {
        return {_query(), f};
    }
};

} // namespace graph

} // namespace hellolin

#endif