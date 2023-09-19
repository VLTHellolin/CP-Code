#ifndef HELLOLIN_GRAPH_SCC_HPP
#define HELLOLIN_GRAPH_SCC_HPP 1
#include <algorithm>
#include <stack>
#include <vector>

namespace hellolin {

namespace graph {

class scc {
    using st = size_t;

private:
    st n;
    int tot = 0, scc_tot = 0;
    std::vector<std::vector<int>> g, node;
    std::vector<bool> vis;
    std::stack<int> q;
    std::vector<int> low, dfn, topo;

public:
    explicit scc(st _n)
        : n(_n) {
        g.resize(n + 1);
        node.resize(n + 1);
        vis.resize(n + 1);
        low.resize(n + 1);
        dfn.resize(n + 1);
        topo.resize(n + 1);
    }
    void add_edge(int u, int v) {
        g[u].push_back(v);
    }
    std::pair<int, std::vector<std::vector<int>>> query() {
        auto tarjan = [&](auto fun, int x) -> void {
            low[x] = dfn[x] = ++tot;
            vis[x] = 1;
            q.push(x);
            for (int y : g[x]) {
                if (!dfn[y]) {
                    fun(fun, y);
                    low[x] = std::min(low[x], low[y]);
                } else if (vis[y]) {
                    low[x] = std::min(low[x], dfn[y]);
                }
            }
            if (low[x] == dfn[x]) {
                ++scc_tot;
                int tp = -1;
                do {
                    tp = q.top(), q.pop();
                    node[scc_tot].push_back(tp);
                    topo[tp] = scc_tot;
                    vis[tp] = 0;
                } while (tp != x);
            }
        };
        for (int i = 1; i <= n; i++)
            if (!dfn[i]) tarjan(tarjan, i);
        for (int i = 1; i <= n; i++) {
            std::sort(node[i].begin(), node[i].end());
            node[i].erase(std::unique(node[i].begin(), node[i].end()), node[i].end());
        }
        return {scc_tot, node};
    }
    std::vector<int> &get_topo() {
        return topo;
    }
};

} // namespace graph

} // namespace hellolin

#endif