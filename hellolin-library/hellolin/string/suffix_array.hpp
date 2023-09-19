#ifndef HELLOLIN_STRING_SUFFIX_ARRAY_HPP
#define HELLOLIN_STRING_SUFFIX_ARRAY_HPP 1
#include <string>
#include <vector>

namespace hellolin {

namespace string {

// ! 约定下标从 1 开始
class suffix_array {
    constexpr static int CHS = 127; // ASCII

public:
    std::vector<int> sa, rk;

private:
    int n, now, t;
    std::vector<int> oldsa, oldrk, key, tp;
    std::string s;

    void csort_1() {
        for (int i = 1; i <= n; i++)
            ++tp[rk[i] = s[i]];
        for (int i = 1; i <= CHS; i++)
            tp[i] += tp[i - 1];
        for (int i = n; i >= 1; i--)
            sa[tp[rk[i]]--] = i;
    }
    void csort_k(int k) {
        for (int i = 1; i <= n; i++)
            ++tp[key[i] = rk[oldsa[i]]];
        for (int i = 1; i <= k; i++)
            tp[i] += tp[i - 1];
        for (int i = n; i >= 1; i--)
            sa[tp[key[i]]--] = oldsa[i];
    }
    bool clash(int x, int y, int k) {
        return oldrk[x] == oldrk[y] && oldrk[x + k] == oldrk[y + k];
    }
    void set_sa() {
        csort_1();
        now = CHS;
        t = 0;
        for (int w = 1; t != n; w <<= 1, now = t) {
            int i = n;
            for (t = 0; i > n - w; i--)
                oldsa[++t] = i;
            for (i = 1; i <= n; i++)
                if (sa[i] > w) oldsa[++t] = sa[i] - w;

            std::fill(tp.begin(), tp.end(), 0);
            csort_k(now);

            std::copy(rk.begin(), rk.end(), oldrk.begin());
            for (t = 0, i = 1; i <= n; i++)
                rk[sa[i]] = clash(sa[i], sa[i - 1], w) ? t : ++t;
        }
    }

public:
    suffix_array() {}
    explicit suffix_array(std::string _s, int tp_size = 1e7) {
        set(_s, tp_size);
    }
    void set(std::string _s, int tp_size = 1e7) {
        s = _s;
        n = s.length();
        s = ' ' + s;
        sa.resize(n + 11, 0);
        rk.resize(n + 11, 0);
        oldsa.resize(n + 11, 0);
        oldrk.resize((n << 1) + 11, 0);
        key.resize(n + 11, 0);
        tp.resize(tp_size, 0);

        set_sa();
    }
};

} // namespace string

} // namespace hellolin

#endif