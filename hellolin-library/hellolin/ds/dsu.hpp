#ifndef HELLOLIN_DS_DSU_HPP
#define HELLOLIN_DS_DSU_HPP 1
#include <algorithm>
#include <vector>

namespace hellolin {

namespace ds {

class dsu {
private:
    int n;
    std::vector<int> g;

public:
    explicit dsu(int _n)
        : n(_n) {
        g.resize(n + 1, -1);
    }

    int find(int x) {
        return g[x] < 0 ? x : g[x] = find(g[x]);
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    int size(int x) {
        return -g[find(x)];
    }
    int merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return x;
        if (-g[x] < -g[y]) std::swap(x, y);
        g[x] += g[y];
        g[y] = x;
        return x;
    }
    void erase(int x) {
        ++g[find(x)];
        g[x] = -1;
    }
    void swap(int x, int y) {
        int _x = x;
        x = find(x), y = find(y);
        if(x==y) return;
        g[_x] = y;
        ++g[x], --g[y];
    }
};

} // namespace ds

} // namespace hellolin

#endif
