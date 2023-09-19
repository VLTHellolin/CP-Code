#ifndef HELLOLIN_GRAPH_BCC_HPP
#define HELLOLIN_GRAPH_BCC_HPP 1
#include <algorithm>
#include <stack>
#include <vector>

namespace hellolin {

namespace graph {

class v_bcc {
    using st = size_t;

private:
    st n;
    int tot = 0, bcc_tot = 0;
    std::vector<int> dfn, low, ind;
    std::vector<std::vector<int>> g, ans;
    std::stack<int> q;

public:
    explicit v_bcc(st _n)
        : n(_n) {
        dfn.resize(n + 1);
        low.resize(n + 1);
        ind.resize(n + 1);
        g.resize(n + 1);
        ans.resize(n + 1);
    }
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
        ++ind[u], ++ind[v];
    }
    std::pair<int, std::vector<std::vector<int>>> query() {
        auto tarjan = [&](auto fun, int x) -> void {
            low[x] = dfn[x] = ++tot;
            q.push(x);
            if (!ind[x]) {
                ans[++bcc_tot].push_back(x);
            }
            for (int y : g[x]) {
                if (!dfn[y]) {
                    fun(fun, y);
                    low[x] = std::min(low[x], low[y]);
                    if (low[y] >= dfn[x]) {
                        ++bcc_tot;
                        int tp = -1;
                        ans[bcc_tot].push_back(x);
                        do {
                            tp = q.top(), q.pop();
                            ans[bcc_tot].push_back(tp);
                        } while (tp != y);
                    }
                } else {
                    low[x] = std::min(low[x], dfn[y]);
                }
            }
        };

        for (int i = 1; i <= n; i++)
            if (!dfn[i]) tarjan(tarjan, i);
        for (int i = 1; i <= n; i++) {
            std::sort(ans[i].begin(), ans[i].end());
            ans[i].erase(std::unique(ans[i].begin(), ans[i].end()), ans[i].end());
        }
        return {bcc_tot, ans};
    }
};

class e_bcc {
    using st = size_t;

private:
    st n;
    int tot = 0, bcc_tot = 0, cnt = 1;
    std::vector<int> dfn, low;
    std::vector<std::vector<std::pair<int, int>>> g;
    std::vector<std::vector<int>> ans;
    std::stack<int> q;

public:
    explicit e_bcc(st _n)
        : n(_n) {
        dfn.resize((n << 1) + 2);
        low.resize((n << 1) + 2);
        g.resize((n << 1) + 2);
        ans.resize(n + 1);
    }
    void add_edge(int u, int v) {
        g[u].push_back({v, ++cnt});
    }
    std::pair<int, std::vector<std::vector<int>>> query() {
        auto tarjan = [&](auto fun, int x, int ed) -> void {
            low[x] = dfn[x] = ++tot;
            q.push(x);
            for (auto qwq : g[x]) {
                int y = qwq.first;
                if (!dfn[y]) {
                    fun(fun, y, qwq.second);
                    low[x] = std::min(low[x], low[y]);
                    if (low[y] > dfn[x]) {
                        ++bcc_tot;
                        int tp = -1;
                        do {
                            tp = q.top(), q.pop();
                            ans[bcc_tot].push_back(tp);
                        } while (tp != y);
                    }
                } else if (qwq.second != (ed ^ 1)) {
                    low[x] = std::min(low[x], dfn[y]);
                }
            }
        };

        for (int i = 1; i <= n; i++)
            if (!dfn[i]) {
                add_edge(i + n, i);
                tarjan(tarjan, i + n, 0);
            }
        for (int i = 1; i <= n; i++) {
            std::sort(ans[i].begin(), ans[i].end());
            ans[i].erase(std::unique(ans[i].begin(), ans[i].end()), ans[i].end());
        }
        return {bcc_tot, ans};
    }
};

} // namespace graph

} // namespace hellolin
#endif