#include <vector>
#include <algorithm>

class Solution {
public:
    long long maxAlternatingSum(std::vector<int>& nums) {
        int n = nums.size();
        
        // Element ko unke squares ke according descending order mein sort karna
        std::sort(nums.begin(), nums.end(), [](int a, int b) {
            return (long long)a * a > (long long)b * b;
        });
        
        long long score = 0;
        int pos_count = (n + 1) / 2; // Kitne elements positive sign lenge
        
        for (int i = 0; i < n; ++i) {
            long long sq = (long long)nums[i] * nums[i];
            if (i < pos_count) {
                score += sq; // Bade squares ko add karo
            } else {
                score -= sq; // Chhote squares ko subtract karo
            }
        }
        
        return score;
    }
};