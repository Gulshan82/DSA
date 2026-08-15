class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int total_xor = 0;
        int zero_count = 0;
        int n = nums.size();
        
        for (int x : nums) {
            total_xor ^= x;
            if (x == 0) {
                zero_count++;
            }
        }
        
        if (total_xor != 0) {
            return n;
        }
        
        if (zero_count == n) {
            return 0;
        }
        
        return n - 1;
    }
};