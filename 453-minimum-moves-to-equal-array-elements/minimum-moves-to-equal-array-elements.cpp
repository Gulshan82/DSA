#pragma GCC optimize("O3,unroll-loops")
#include <vector>
#include <algorithm>

class Solution {
public:
    int minMoves(std::vector<int>& nums) {
        int min_val = *std::min_element(nums.begin(), nums.end());
        int moves = 0;
        
        for (int num : nums) {
            moves += (num - min_val);
        }
        
        return moves;
    }
};