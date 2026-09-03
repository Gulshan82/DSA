#include <vector>
#include <algorithm>

class Solution {
public:
    bool uniformArray(std::vector<int>& nums1) {
        int min_val = *std::min_element(nums1.begin(), nums1.end());
        
        if (min_val % 2 != 0) {
            return true;
        }
        
        for (int num : nums1) {
            if (num % 2 != 0) {
                return false;
            }
        }
        
        return true;
    }
};