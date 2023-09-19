#ifndef HELLOLIN_GRAPH_EULER_HPP
#define HELLOLIN_GRAPH_EULER_HPP 1
#include <algorithm>
#include <vector>

namespace hellolin {

namespace graph {

class euler {
    using st = size_t;

private:
    st n, m, e_cnt = 0, e_tot = 0;
    bool directed, ready;
    int tp = 1;
    class verticle {
    public:
        int no = 0;
        int to = 0, nxt = 0;
        int T = 0;
    };
    std::vector<verticle> g;
    std::vector<bool> vis;
    std::vector<int> head, ans, ind, oud, cur;

public:
    explicit euler(st _n, st _m, bool _directed = 0)
        : n(_n)
        , m(_m)
        , directed(_directed)
        , ready(0) {
        g.resize((m<<1) + 2);
        head.resize(n + 1);
        vis.resize(m + 1);
        ans.resize(m + 1);
        ind.resize(n + 1);
        oud.resize(n + 1);
        cur.resize(n + 1);
    }
    void add_edge(int u, int v, int x) {
        ready = 0;
        tp = u;
        ++oud[u], ++ind[v];
        g[++e_cnt] = {x, v, head[u], 1};
        head[u] = e_cnt;
        if (!directed) {
            g[++e_cnt] = {x, u, head[v], -1};
            head[v] = e_cnt;
        }
    }
    bool query() {
        ready = 1;
        auto hierholzer = [&](auto fun, int x) -> void {
            for(int &i = cur[x]; i; i=g[i].nxt) {
                if(vis[g[i].no]) continue;
                vis[g[i].no] = 1;
                int _ans = g[i].T * g[i].no;
                fun(fun, g[i].to);
                ans[++e_tot] = _ans;
            }
        };

        for (int i = 1; i <= n; i++)
            if (directed) {
                if (ind[i] != oud[i])
                    return 0;
            } else {
                if ((ind[i] + oud[i]) & 1)
                    return 0;
            }

        for (int i = 1; i <= n; i++)
            cur[i] = head[i];
        hierholzer(hierholzer, tp);
        if (e_tot < m)
            return 0;
        
        std::reverse(ans.begin()+1, ans.begin()+1+m);
        return 1;
    }
    std::vector<int> &get_ans() {
        if(!ready) query();
        return ans;
    }
};

} // namespace graph

} // namespace hellolin
#endif