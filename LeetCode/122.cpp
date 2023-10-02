#include <bits/stdc++.h>

namespace hellolin_leet {
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size(), res = 0;
        for(int i = 1; i < n; ++i) res += max(0, prices[i] - prices[i - 1]);
        return res;
    }
};

}

using hellolin_leet::Solution;