#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
public:
    int maxLength(std::vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return (n == 1 && nums[0] == 1) ? 1 : 0;
        
        int ans = 2;
        long long cur_prod = 1;
        int l = 0;
        
        for (int r = 0; r < n; ++r) {
            while (std::gcd(cur_prod, (long long)nums[r]) > 1) {
                cur_prod /= nums[l++];
            }
            cur_prod *= nums[r];
            ans = std::max(ans, r - l + 1);
        }
        
        return ans;
    }
};