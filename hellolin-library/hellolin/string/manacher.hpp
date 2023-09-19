#ifndef HELLOLIN_STRING_MANACHER_HPP
#define HELLOLIN_STRING_MANACHER_HPP 1
#include <algorithm>
#include <string>
#include <vector>

namespace hellolin {

namespace string {

// ! 约定下标从 1 开始
class manacher {
private:
    int n;
    std::string s, tp;
    std::vector<int> q;

    void init_tp() {
        tp = " #";
        for (int i = 1; i <= n; i++) {
            tp += s[i];
            tp += '#';
        }
        n = tp.length() - 1;
    }
    int calc_ans() {
        q[1] = 1;
        int r = 1;
        for (int l = 2; l <= n; l++) {
            if (l <= r) q[l] = std::min(r - l + 1, q[r - l + 1]);
            while (tp[l - q[l]] == tp[l + q[l]])
                ++q[l];
            if (q[l] + l > r + 1) {
                r = l + q[l] - 1;
            }
        }
        return (*std::max_element(q.begin(), q.end())) - 1;
    }

public:
    manacher() {}
    explicit manacher(std::string _s) {
        set(_s);
    }
    void set(std::string _s) {
        s = _s;
        n = s.length();
        s = ' ' + s;
        q.resize((n << 1) + 11, 0);
    }
    int query() {
        init_tp();
        return calc_ans();
    }
};

} // namespace string

} // namespace hellolin

#endif