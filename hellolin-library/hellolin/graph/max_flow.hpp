#ifndef HELLOLIN_GRAPH_MAX_FLOW_HPP
#define HELLOLIN_GRAPH_MAX_FLOW_HPP 1
#include <algorithm>
#include <limits>
#include <queue>
#include <vector>

namespace hellolin {

namespace graph {

template <class T>
class max_flow {
private:
    int n, m;
    std::vector<std::pair<int, int>> pr;
    class internal_edge {
    public:
        int to, p;
        T w;
    };
    std::vector<std::vector<internal_edge>> g;
    std::vector<bool> vis;
    std::queue<int> q;
    std::vector<int> s_l, s_t;

    void _bfs(int fr, int to) {
        std::fill(s_l.begin(), s_l.end(), -1);
        q = std::queue<int>();
        q.push(fr);
        s_l[fr] = 0;
        while (q.size()) {
            int tp = q.front();
            q.pop();
            for (internal_edge i : g[tp]) {
                if (i.w && s_l[i.to] < 0) {
                    s_l[i.to] = s_l[tp] + 1;
                    if (i.to == to) return;
                    q.push(i.to);
                }
            }
        }
    }
    T _dfs(int tar, int now, T p) {
        if (now == tar) return p;
        T res = 0;
        int sn = s_l[now];
        for (int &i = s_t[now]; i < (int) g[now].size(); i++) {
            internal_edge &e1 = g[now][i];
            internal_edge &e2 = g[e1.to][e1.p];
            if (sn > s_l[e1.to] && e2.w) {
                T qwq = _dfs(tar, e1.to, std::min(p - res, e2.w));
                if (qwq <= 0) continue;
                e1.w += qwq;
                e2.w -= qwq;
                res += qwq;
                if (res == p) return res;
            }
        }
        s_l[now] = n;
        return res;
    }

public:
    class edge {
        int fr, to;
        T w, flow;
    };
    explicit max_flow(int _n)
        : n(_n) {
        g.resize(n + 1);
        vis.resize(n + 1);
    }
    void add_edge(int fr, int to, T w) {
        m = pr.size();
        int _fr = g[fr].size(), _to = g[to].size();
        if (fr == to) ++_to;
        pr.push_back({fr, _fr});
        g[fr].push_back(internal_edge{to, _to, w});
        g[to].push_back(internal_edge{fr, _fr, 0});
    }
    edge get_edge(int x) {
        m = pr.size();
        internal_edge e1, e2;
        e1 = g[pr[x].first][pr[x].second];
        e2 = g[e1.to][e1.p];
        return edge{pr[x].first, e1.to, e1.w + e2.w, e2.w};
    }
    std::vector<edge> get_edges() {
        m = pr.size();
        std::vector<edge> e;
        for (int i = 0; i < m; i++) {
            e.push_back(get_edge(i));
        }
        return e;
    }
    void modify_edge(int x, T _w, T _flow) {
        m = pr.size();
        internal_edge &e1 = g[pr[x].first][pr[x].second];
        internal_edge &e2 = g[e1.to][e1.p];
        e1.w = _w - _flow;
        e2.w = _flow;
    }
    T get_flow(int fr, int to, T lim = std::numeric_limits<T>::max()) {
        T res = 0;
        s_l.resize(n + 1);
        s_t.resize(n + 1);
        while (res < lim) {
            _bfs(fr, to);
            std::fill(s_t.begin(), s_t.end(), 0);
            if (s_l[to] == -1) return res;
            T qwq = _dfs(fr, to, lim - res);
            if (!qwq) return res;
            res += qwq;
        }
        return res;
    }
    std::vector<bool> min_cut(int x) {
        vis.resize(n + 1, 0);
        q = std::queue<int>();
        q.push(x);
        while (q.size()) {
            int tp = q.front();
            q.pop();
            if (vis[tp]) continue;
            vis[tp] = 1;
            for (internal_edge i : g[tp]) {
                if (i.w && !vis[i.to]) {
                    q.push(i.to);
                }
            }
        }
        return vis;
    }
};

} // namespace graph

} // namespace hellolin

#endif