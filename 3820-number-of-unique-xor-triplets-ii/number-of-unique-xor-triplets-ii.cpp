class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int max_val = 0;
        for (int x : nums) {
            if (x > max_val) {
                max_val = x;
            }
        }
        
        int limit = 1;
        while (limit <= max_val) {
            limit *= 2;
        }
        
        if (limit <= 10000000) {
            vector<bool> present(limit, false);
            vector<int> unique_nums;
            for (int x : nums) {
                if (!present[x]) {
                    present[x] = true;
                    unique_nums.push_back(x);
                }
            }
            
            vector<bool> pairs(limit, false);
            for (int i = 0; i < unique_nums.size(); ++i) {
                for (int j = i; j < unique_nums.size(); ++j) {
                    pairs[unique_nums[i] ^ unique_nums[j]] = true;
                }
            }
            
            int count = 0;
            vector<bool> triplets(limit, false);
            for (int p = 0; p < limit; ++p) {
                if (pairs[p]) {
                    for (int x : unique_nums) {
                        int t = p ^ x;
                        if (!triplets[t]) {
                            triplets[t] = true;
                            count++;
                        }
                    }
                }
            }
            return count;
        } else {
            unordered_set<int> unique_nums(nums.begin(), nums.end());
            unordered_set<int> pairs;
            for (int x : unique_nums) {
                for (int y : unique_nums) {
                    pairs.insert(x ^ y);
                }
            }
            
            unordered_set<int> triplets;
            for (int p : pairs) {
                for (int x : unique_nums) {
                    triplets.insert(p ^ x);
                }
            }
            return triplets.size();
        }
    }
};