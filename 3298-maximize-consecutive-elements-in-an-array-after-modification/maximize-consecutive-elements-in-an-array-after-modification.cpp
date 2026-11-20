#pragma GCC optimize("O3,unroll-loops")
#include <vector>
#include <algorithm>

class Solution {
public:
    int maxSelectedElements(std::vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        
        int max_val = nums.back();
        std::vector<int> dp(max_val + 2, 0);
        int ans = 0;
        
        for (int x : nums) {
            dp[x + 1] = dp[x] + 1;
            dp[x] = dp[x - 1] + 1;
            ans = std::max({ans, dp[x], dp[x + 1]});
        }
        
        return ans;
    }
};