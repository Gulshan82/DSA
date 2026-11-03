#pragma GCC optimize("O3,unroll-loops")
#include <vector>
#include <algorithm>

class Solution {
public:
    int minMoves(std::vector<int>& nums) {
        int max_val = *std::max_element(nums.begin(), nums.end());
        int moves = 0;
        
        for (int num : nums) {
            moves += (max_val - num);
        }
        
        return moves;
    }
};