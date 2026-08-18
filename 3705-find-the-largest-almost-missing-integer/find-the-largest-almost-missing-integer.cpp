class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        unordered_map<int, int> subarray_counts;
        int n = nums.size();
        
        for (int i = 0; i <= n - k; ++i) {
            unordered_set<int> window(nums.begin() + i, nums.begin() + i + k);
            for (int num : window) {
                subarray_counts[num]++;
            }
        }
        
        int max_val = -1;
        for (auto const& [num, count] : subarray_counts) {
            if (count == 1) {
                max_val = max(max_val, num);
            }
        }
        
        return max_val;
    }
};