#include <vector>

class Solution {
public:
    int countGoodRotations(std::vector<int>& nums) {
        int n = nums.size();
        int half = n / 2;
        long long total_sum = 0;
        long long window_sum = 0;
        
        for (int i = 0; i < n; ++i) {
            total_sum += nums[i];
            if (i < half) {
                window_sum += nums[i];
            }
        }
        
        int count = 0;
        if (window_sum * 2 > total_sum) {
            count++;
        }
        
        for (int i = 1; i < n; ++i) {
            window_sum -= nums[i - 1];
            window_sum += nums[(i + half - 1) % n];
            
            if (window_sum * 2 > total_sum) {
                count++;
            }
        }
        
        return count;
    }
};