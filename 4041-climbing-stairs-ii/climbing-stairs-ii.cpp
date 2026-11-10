#pragma GCC optimize("O3,unroll-loops")
#include <vector>
#include <algorithm>

class Solution {
public:
    int climbStairs(int n, std::vector<int>& costs) {
        long long dp1 = 0;
        long long dp2 = 1e18;
        long long dp3 = 1e18;
        
        for (int i = 1; i <= n; ++i) {
            long long c = costs[i - 1];
            long long cur = dp1 + 1 + c;
            
            if (i >= 2) cur = std::min(cur, dp2 + 4 + c);
            if (i >= 3) cur = std::min(cur, dp3 + 9 + c);
            
            dp3 = dp2;
            dp2 = dp1;
            dp1 = cur;
        }
        
        return dp1;
    }
};