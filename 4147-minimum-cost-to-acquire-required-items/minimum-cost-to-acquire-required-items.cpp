#pragma GCC optimize("O3,unroll-loops")
#include <algorithm>

class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
        auto calc = [&](long long x) {
            long long rem1 = (need1 > x) ? (need1 - x) : 0;
            long long rem2 = (need2 > x) ? (need2 - x) : 0;
            return x * costBoth + rem1 * cost1 + rem2 * cost2;
        };
        
        return std::min({calc(0), calc(need1), calc(need2)});
    }
};