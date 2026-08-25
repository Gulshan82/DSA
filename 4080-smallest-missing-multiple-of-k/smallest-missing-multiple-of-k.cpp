class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        unordered_set<int> num_set(nums.begin(), nums.end());
        int mult = k;
        
        while (num_set.count(mult)) {
            mult += k;
        }
        
        return mult;
    }
};