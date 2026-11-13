#pragma GCC optimize("O3,unroll-loops")
#include <vector>
#include <algorithm>

struct Block {
    int idx;
    long long max_val;
    long long sum_cost;
};

class Solution {
public:
    long long countNonDecreasingSubarrays(std::vector<int>& nums, int k) {
        int n = nums.size();
        std::vector<long long> pref(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            pref[i + 1] = pref[i] + nums[i];
        }
        
        std::vector<Block> st;
        long long ans = 0;
        
        for (int i = n - 1; i >= 0; --i) {
            while (!st.empty() && st.back().max_val <= nums[i]) {
                st.pop_back();
            }
            
            int next_idx = st.empty() ? n : st.back().idx;
            long long block_cost = (long long)(next_idx - i) * nums[i] - (pref[next_idx] - pref[i]);
            long long current_sum_cost = block_cost + (st.empty() ? 0LL : st.back().sum_cost);
            
            st.push_back({i, (long long)nums[i], current_sum_cost});
            
            long long total_c = current_sum_cost;
            long long target = total_c - k;
            
            if (target <= 0) {
                ans += (n - i);
            } else {
                auto it = std::lower_bound(st.begin(), st.end(), target, 
                    [](const Block& b, long long val) {
                        return b.sum_cost < val;
                    });
                
                int m = it - st.begin();
                long long base_cost = (m > 0) ? st[m - 1].sum_cost : 0LL;
                long long required = target - base_cost;
                
                int next_B_idx = (m > 0) ? st[m - 1].idx : n;
                int low = it->idx;
                int high = next_B_idx - 1;
                long long best_x = low;
                long long B_max = it->max_val;
                
                while (low <= high) {
                    int mid = low + (high - low) / 2;
                    long long c = (long long)(next_B_idx - mid) * B_max - (pref[next_B_idx] - pref[mid]);
                    if (c >= required) {
                        best_x = mid;
                        low = mid + 1;
                    } else {
                        high = mid - 1;
                    }
                }
                ans += (best_x - i);
            }
        }
        
        return ans;
    }
};