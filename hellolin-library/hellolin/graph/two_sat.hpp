#ifndef HELLOLIN_GRAPH_TWO_SAT_HPP
#define HELLOLIN_GRAPH_TWO_SAT_HPP 1
#include <algorithm>
#include <stack>
#include <vector>

namespace hellolin {

namespace graph {

class two_sat {
    using st = size_t;

private:
    bool ready;
    st n;
    int tot, scc_tot;
    std::vector<bool> ans, vis;
    std::stack<int> q;
    std::vector<std::vector<int>> g;
    std::vector<int> low, dfn, topo;

public:
    explicit two_sat(st _n)
        : n(_n)
        , ready(0) {
        ans.resize(n + 1);
        g.resize((n << 1) + 2);
        low.resize((n << 1) + 2);
        dfn.resize((n << 1) + 2);
        topo.resize((n << 1) + 2);
        vis.resize((n << 1) + 2);
    }
    void add_clause(int x, bool xv, int y, bool yv) {
        ready = 0;
        g[x + n * (xv & 1)].push_back(y + n * (yv ^ 1));
        g[y + n * (yv & 1)].push_back(x + n * (xv ^ 1));
    }
    void add_edge(int x, int y) {
        g[x].push_back(y);
    }
    bool query() {
        ready = 1;
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
                do {
                    topo[x] = scc_tot;
                    x = q.top(), q.pop();
                    vis[x] = 0;
                } while (low[x] != dfn[x]);
            }
        };
        for (int i = 1; i <= (n << 1); i++)
            if (!dfn[i]) tarjan(tarjan, i);
        for (int i = 1; i <= n; i++)
            if (topo[i] == topo[n + i]) return 0;
        for (int i = 1; i <= n; i++)
            ans[i] = topo[i] < topo[n + i];
        return 1;
    }
    std::vector<bool> get_ans() {
        if (!ready) query();
        return ans;
    }
};

} // namespace graph

} // namespace hellolin

#endif