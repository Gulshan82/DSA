#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution {
public:
    int minSumOfLengths(std::vector<int>& arr, int target) {
        int n = arr.size();
        std::unordered_map<int, int> prefix_map;
        prefix_map[0] = -1;
        
        std::vector<int> dp(n, 1e9); 
        int sum = 0;
        int ans = 1e9;
        int min_len_so_far = 1e9;
        
        for (int i = 0; i < n; ++i) {
            sum += arr[i];
            prefix_map[sum] = i;
            
            if (prefix_map.count(sum - target)) {
                int prev_idx = prefix_map[sum - target];
                int len = i - prev_idx;
                
                if (prev_idx >= 0 && dp[prev_idx] != 1e9) {
                    ans = std::min(ans, len + dp[prev_idx]);
                }
                min_len_so_far = std::min(min_len_so_far, len);
            }
            dp[i] = min_len_so_far;
        }
        
        return ans == 1e9 ? -1 : ans;
    }
};