#pragma GCC optimize("O3,unroll-loops")
#include <vector>
#include <algorithm>

class Solution {
public:
    int longestMonotonicSubarray(std::vector<int>& nums) {
        if (nums.empty()) return 0;
        
        int max_len = 1;
        int inc = 1;
        int dec = 1;
        
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] > nums[i - 1]) {
                inc++;
                dec = 1;
            } else if (nums[i] < nums[i - 1]) {
                dec++;
                inc = 1;
            } else {
                inc = 1;
                dec = 1;
            }
            max_len = std::max({max_len, inc, dec});
        }
        
        return max_len;
    }
};