#ifndef HELLOLIN_STRING_LYNDON_HPP
#define HELLOLIN_STRING_LYNDON_HPP 1
#include <string>
#include <vector>

namespace hellolin {

namespace string {

std::vector<std::pair<int, int>> lyndon(std::string s) {
    std::vector<std::pair<int, int>> ans;
    int n = s.size();
    s = ' ' + s;
    int x = 0, y = 0;
    for (int i = 1; i <= n;) {
        for (x = i, y = i + 1; y <= n && s[x] <= s[y]; y++) {
            if (s[x] < s[y])
                x = i;
            else
                ++x;
        }
        while (i <= x) {
            ans.emplace_back(i, i + y - x - 1);
            i += y - x;
        }
    }
    return ans;
}

} // namespace string

} // namespace hellolin

#endif