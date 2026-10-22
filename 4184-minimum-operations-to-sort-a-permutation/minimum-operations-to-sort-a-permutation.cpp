#include <vector>
#include <algorithm>

class Solution {
public:
    int minOperations(std::vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 0;
        
        int pos_0 = -1;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == 0) {
                pos_0 = i;
                break;
            }
        }
        
        // Check if the array is a cyclic shift of the forward sorted array (0, 1, 2...)
        bool is_forward = true;
        for (int i = 0; i < n; ++i) {
            if (nums[(pos_0 + i) % n] != i) {
                is_forward = false;
                break;
            }
        }
        
        // Check if the array is a cyclic shift of the backward sorted array (0, n-1, n-2...)
        bool is_backward = true;
        for (int i = 0; i < n; ++i) {
            if (nums[(pos_0 - i + n) % n] != i) {
                is_backward = false;
                break;
            }
        }
        
        // If it doesn't match either pattern, it's impossible to sort with given operations
        if (!is_forward && !is_backward) {
            return -1;
        }
        
        int min_ops = 1e9;
        
        if (is_forward) {
            // Path 1: Rotate left pos_0 times
            // Path 2: Reverse, rotate left (n - pos_0) times, reverse again
            min_ops = std::min(min_ops, std::min(pos_0, n - pos_0 + 2));
        }
        
        if (is_backward) {
            // Path 1: Reverse, then rotate left (n - pos_0) times
            // Path 2: Rotate left (pos_0 + 1) times, then reverse
            min_ops = std::min(min_ops, std::min(n - pos_0, pos_0 + 2));
        }
        
        return min_ops;
    }
};