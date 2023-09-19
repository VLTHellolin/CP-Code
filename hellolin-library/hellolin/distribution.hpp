#ifndef HELLOLIN_DISTRIBUTION_HPP
#define HELLOLIN_DISTRIBUTION_HPP 1
#include <algorithm>
#include <vector>

namespace hellolin {

template <class T>
class distribution {
private:
    bool ready;
    std::vector<T> d;
    void init() {
        std::sort(d.begin(), d.end());
        d.erase(std::unique(d.begin(), d.end()), d.end());
        ready = 1;
    }

public:
    explicit distribution()
        : ready(0) {}
    void push(T x) {
        d.emplace_back(x);
        ready = 0;
    }
    template <class... Args>
    void push(T x, Args... y) {
        push(x);
        push(y...);
    }
    int distribute(T x) {
        if (!ready) init();
        return std::lower_bound(d.begin(), d.end(), x) - d.begin() + 1;
    }
    T tribute(int x) {
        if (!ready) init();
        return d[x - 1];
    }
    int size() {
        if (!ready) init();
        return d.size();
    }
    void clear() {
        d.clear();
    }
};

} // namespace hellolin

#endif