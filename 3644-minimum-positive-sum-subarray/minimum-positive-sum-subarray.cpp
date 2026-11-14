#pragma GCC optimize("O3,unroll-loops")
#include <vector>
#include <algorithm>

class Solution {
public:
    int minimumSumSubarray(std::vector<int>& nums, int l, int r) {
        int n = nums.size();
        int min_pos_sum = 1e9;
        
        for (int i = 0; i < n; ++i) {
            int current_sum = 0;
            for (int j = i; j < n; ++j) {
                current_sum += nums[j];
                int length = j - i + 1;
                
                if (length >= l && length <= r && current_sum > 0) {
                    if (current_sum < min_pos_sum) {
                        min_pos_sum = current_sum;
                    }
                }
            }
        }
        
        return min_pos_sum == 1e9 ? -1 : min_pos_sum;
    }
};