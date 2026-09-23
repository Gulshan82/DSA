#include <vector>
#include <algorithm>

class Solution {
public:
    int minOperations(std::vector<int>& nums, int x) {
        long long total_sum = 0;
        for (int num : nums) {
            total_sum += num;
        }
        
        long long target = total_sum - x;
        
        // Agar target negative hai, toh x banana possible nahi hai
        if (target < 0) return -1;
        
        // Agar target 0 hai, toh saare elements remove karne padenge
        if (target == 0) return nums.size();
        
        int max_len = -1;
        long long current_sum = 0;
        int left = 0;
        
        // Sliding window se longest subarray find karenge jiska sum 'target' ho
        for (int right = 0; right < nums.size(); ++right) {
            current_sum += nums[right];
            
            while (current_sum > target && left <= right) {
                current_sum -= nums[left];
                left++;
            }
            
            if (current_sum == target) {
                max_len = std::max(max_len, right - left + 1);
            }
        }
        
        return max_len != -1 ? nums.size() - max_len : -1;
    }
};