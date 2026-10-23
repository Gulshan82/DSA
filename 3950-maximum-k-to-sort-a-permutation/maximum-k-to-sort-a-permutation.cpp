#include <vector>

class Solution {
public:
    int sortPermutation(std::vector<int>& nums) {
        int k = -1;
        bool is_sorted = true;
        
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != i) {
                is_sorted = false;
                k &= nums[i];
            }
        }
        
        return is_sorted ? 0 : k;
    }
};