#pragma GCC optimize("O3,unroll-loops")
#include <vector>
#include <algorithm>
#include <cmath>

class Solution {
public:
    int findTheDistanceValue(std::vector<int>& arr1, std::vector<int>& arr2, int d) {
        std::sort(arr2.begin(), arr2.end());
        int count = 0;
        
        for (int val : arr1) {
            auto it = std::lower_bound(arr2.begin(), arr2.end(), val);
            bool is_valid = true;
            
            if (it != arr2.end() && std::abs(*it - val) <= d) {
                is_valid = false;
            }
            if (it != arr2.begin() && std::abs(*(it - 1) - val) <= d) {
                is_valid = false;
            }
            
            if (is_valid) {
                count++;
            }
        }
        
        return count;
    }
};