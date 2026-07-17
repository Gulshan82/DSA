class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int max_val = 0;
        for (int num : nums) {
            if (num > max_val) max_val = num;
        }
        
       
        vector<long long> cnt(max_val + 1, 0);
        for (int num : nums) {
            cnt[num]++;
        }
        
        vector<long long> exact_gcd(max_val + 1, 0);
        
       
        for (int g = max_val; g >= 1; --g) {
            long long multiples_count = 0;
            
            for (int m = g; m <= max_val; m += g) {
                multiples_count += cnt[m];
            }
            
            
            long long pairs = (multiples_count * (multiples_count - 1)) / 2;
            
           
            for (int m = 2 * g; m <= max_val; m += g) {
                pairs -= exact_gcd[m];
            }
            
            exact_gcd[g] = pairs;
        }
        
       
        vector<long long> prefix_cnt(max_val + 1, 0);
        for (int g = 1; g <= max_val; ++g) {
            prefix_cnt[g] = prefix_cnt[g - 1] + exact_gcd[g];
        }
        
       
        vector<int> ans;
        ans.reserve(queries.size());
        
        for (long long q : queries) {
            int left = 1, right = max_val;
            int res = max_val;
            
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (prefix_cnt[mid] > q) {
                    res = mid;
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            ans.push_back(res);
        }
        
        return ans;
    }
};