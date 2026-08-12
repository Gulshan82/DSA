class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        int max_len = 0;
        int left = 0;
        
        for (int right = 0; right < nums.size(); ++right) {
            freq[nums[right]]++;
            
            while (freq[nums[right]] > k) {
                freq[nums[left]]--;
                left++;
            }
            
            max_len = max(max_len, right - left + 1);
        }
        
        return max_len;
    }
};