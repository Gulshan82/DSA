#include <vector>

class Solution {
public:
    int maxSum(std::vector<int>& nums, int k) {
        std::vector<int> count(32, 0);
        
        // Count the number of set bits at each position across all numbers
        for (int num : nums) {
            for (int i = 0; i < 32; ++i) {
                if ((num >> i) & 1) {
                    count[i]++;
                }
            }
        }
        
        long long ans = 0;
        long long mod = 1e9 + 7;
        
        // Greedily construct the k largest possible numbers
        for (int j = 0; j < k; ++j) {
            long long current_val = 0;
            for (int i = 0; i < 32; ++i) {
                if (count[i] > 0) {
                    current_val |= (1LL << i);
                    count[i]--;
                }
            }
            ans = (ans + (current_val * current_val) % mod) % mod;
        }
        
        return ans;
    }
};