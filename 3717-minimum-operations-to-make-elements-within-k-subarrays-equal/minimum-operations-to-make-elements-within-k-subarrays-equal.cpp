#pragma GCC optimize("O3,unroll-loops")
#include <vector>
#include <set>
#include <algorithm>

class Solution {
public:
    long long minOperations(std::vector<int>& nums, int x, int k) {
        int n = nums.size();
        std::vector<long long> cost(n, 0);
        std::multiset<long long> low, high;
        long long sum_low = 0, sum_high = 0;

        auto balance = [&]() {
            while (low.size() > high.size() + 1) {
                auto it = std::prev(low.end());
                high.insert(*it);
                sum_high += *it;
                sum_low -= *it;
                low.erase(it);
            }
            while (high.size() > low.size()) {
                auto it = high.begin();
                low.insert(*it);
                sum_low += *it;
                sum_high -= *it;
                high.erase(it);
            }
        };

        auto add = [&](long long val) {
            if (low.empty() || val <= *low.rbegin()) {
                low.insert(val);
                sum_low += val;
            } else {
                high.insert(val);
                sum_high += val;
            }
            balance();
        };

        auto remove = [&](long long val) {
            auto it = low.find(val);
            if (it != low.end()) {
                low.erase(it);
                sum_low -= val;
            } else {
                it = high.find(val);
                high.erase(it);
                sum_high -= val;
            }
            balance();
        };

        long long max_cost = 0;
        for (int i = 0; i < n; ++i) {
            add(nums[i]);
            if (i >= x) {
                remove(nums[i - x]);
            }
            if (i >= x - 1) {
                long long median = *low.rbegin();
                if (x % 2 == 1) {
                    cost[i] = sum_high - sum_low + median;
                } else {
                    cost[i] = sum_high - sum_low;
                }
                if (cost[i] > max_cost) {
                    max_cost = cost[i];
                }
            }
        }

        // Dynamically bounding the binary search to ensure mid reaches the required negative depth
        long long max_total_cost = (long long)(n / x) * max_cost;
        long long left = -max_total_cost - 2;
        long long right = 1;
        long long best_ans = -1;

        while (left <= right) {
            long long mid = left + (right - left) / 2;

            // Using __int128_t to completely eliminate any overflow risk during Alien's trick 
            std::vector<std::pair<__int128_t, int>> dp(n + 1, {0, 0});
            
            for (int i = 1; i <= n; ++i) {
                dp[i] = dp[i - 1]; 
                if (i >= x) {
                    __int128_t pick_cost = dp[i - x].first + cost[i - 1] + mid;
                    int pick_cnt = dp[i - x].second + 1;
                    
                    if (pick_cost < dp[i].first || (pick_cost == dp[i].first && pick_cnt > dp[i].second)) {
                        dp[i] = {pick_cost, pick_cnt};
                    }
                }
            }

            if (dp[n].second >= k) {
                best_ans = (long long)(dp[n].first - (__int128_t)k * mid);
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return best_ans;
    }
};