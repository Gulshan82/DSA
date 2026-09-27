#include <vector>
#include <algorithm>
#include <unordered_map>

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 + 0x9e3779b9 + (h1<<6) + (h1>>2));
    }
};

class Solution {
public:
    int maxEqualAdjacentPairs(std::vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return 0;
        
        int initial_equal = 0;
        std::unordered_map<std::pair<int, int>, int, pair_hash> counts;
        int max_additional = 0;
        
        for (int i = 0; i < n - 1; ++i) {
            if (nums[i] == nums[i+1]) {
                initial_equal++;
            } else {
                int u = std::min(nums[i], nums[i+1]);
                int v = std::max(nums[i], nums[i+1]);
                max_additional = std::max(max_additional, ++counts[{u, v}]);
            }
        }
        
        return initial_equal + max_additional;
    }
};