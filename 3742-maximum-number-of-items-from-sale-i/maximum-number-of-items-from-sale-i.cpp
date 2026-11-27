#pragma GCC optimize("O3,unroll-loops")
#include <vector>
#include <algorithm>
#include <climits>

class Solution {
public:
    int maximumSaleItems(std::vector<std::vector<int>>& items, int budget) {
        int n = items.size();
        int min_price = INT_MAX;
        int max_factor = 0;
        for (const auto& it : items) {
            if (it[0] > max_factor) max_factor = it[0];
            if (it[1] < min_price) min_price = it[1];
        }

        std::vector<int> free_cnt(n, 0);
        if (max_factor <= 100000) {
            std::vector<int> freq(max_factor + 1, 0);
            for (const auto& it : items) freq[it[0]]++;
            std::vector<int> mult(max_factor + 1, 0);
            for (int f = 1; f <= max_factor; ++f) {
                if (freq[f] == 0) continue;
                int total = 0;
                for (int m = f; m <= max_factor; m += f) {
                    total += freq[m];
                }
                mult[f] = total - 1;
            }
            for (int i = 0; i < n; ++i) {
                free_cnt[i] = mult[items[i][0]];
            }
        } else {
            for (int i = 0; i < n; ++i) {
                int cnt = 0;
                for (int j = 0; j < n; ++j) {
                    if (i != j && items[j][0] % items[i][0] == 0) {
                        cnt++;
                    }
                }
                free_cnt[i] = cnt;
            }
        }

        std::vector<int> dp(budget + 1, 0);
        for (int i = 0; i < n; ++i) {
            int p = items[i][1];
            int val = 1 + free_cnt[i];
            for (int c = budget; c >= p; --c) {
                dp[c] = std::max(dp[c], dp[c - p] + val);
            }
        }

        int ans = 0;
        for (int c = 0; c <= budget; ++c) {
            ans = std::max(ans, dp[c] + (budget - c) / min_price);
        }

        return ans;
    }
};