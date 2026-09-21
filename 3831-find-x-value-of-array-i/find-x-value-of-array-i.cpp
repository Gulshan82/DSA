#include <vector>
#include <unordered_map>

class Solution {
public:
    std::vector<long long> resultArray(std::vector<int>& nums, int k) {
        std::vector<long long> result(k, 0);
        std::unordered_map<int, long long> current_counts;
        
        for (int num : nums) {
            std::unordered_map<int, long long> next_counts;
            long long val = num % k;
            next_counts[val]++;
            
            for (auto const& [prev_val, count] : current_counts) {
                long long new_val = (prev_val * val) % k;
                next_counts[new_val] += count;
            }
            
            for (auto const& [curr_val, count] : next_counts) {
                result[curr_val] += count;
            }
            
            current_counts = std::move(next_counts);
        }
        
        return result;
    }
};