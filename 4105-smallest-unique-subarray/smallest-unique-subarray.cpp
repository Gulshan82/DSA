#pragma GCC optimize("O3,unroll-loops")
#include <vector>
#include <algorithm>

class Solution {
public:
    int smallestUniqueSubarray(std::vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return n;

        std::vector<int> vals = nums;
        std::sort(vals.begin(), vals.end());
        vals.erase(std::unique(vals.begin(), vals.end()), vals.end());

        std::vector<int> rk(n), sa(n), tmp(n), cnt(n);
        for (int i = 0; i < n; ++i) {
            rk[i] = std::lower_bound(vals.begin(), vals.end(), nums[i]) - vals.begin();
        }

        int classes = vals.size();
        for (int i = 0; i < n; ++i) cnt[rk[i]]++;
        for (int i = 1; i < classes; ++i) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; --i) sa[--cnt[rk[i]]] = i;

        for (int k = 1; k < n && classes < n; k <<= 1) {
            int p = 0;
            for (int i = n - k; i < n; ++i) tmp[p++] = i;
            for (int i = 0; i < n; ++i) {
                if (sa[i] >= k) tmp[p++] = sa[i] - k;
            }

            std::fill(cnt.begin(), cnt.begin() + classes, 0);
            for (int i = 0; i < n; ++i) cnt[rk[tmp[i]]]++;
            for (int i = 1; i < classes; ++i) cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; --i) sa[--cnt[rk[tmp[i]]]] = tmp[i];

            tmp[sa[0]] = 0;
            classes = 1;
            for (int i = 1; i < n; ++i) {
                int cur = sa[i], prev = sa[i - 1];
                int cur2 = (cur + k < n) ? rk[cur + k] : -1;
                int prev2 = (prev + k < n) ? rk[prev + k] : -1;
                if (rk[cur] != rk[prev] || cur2 != prev2) classes++;
                tmp[cur] = classes - 1;
            }
            rk.swap(tmp);
        }

        for (int i = 0; i < n; ++i) rk[sa[i]] = i;

        std::vector<int> lcp(n, 0);
        int h = 0;
        for (int i = 0; i < n; ++i) {
            if (rk[i] == n - 1) {
                h = 0;
                continue;
            }
            int j = sa[rk[i] + 1];
            while (i + h < n && j + h < n && nums[i + h] == nums[j + h]) {
                h++;
            }
            lcp[rk[i]] = h;
            if (h > 0) h--;
        }

        int ans = n;
        for (int i = 0; i < n; ++i) {
            int max_match = 0;
            if (i > 0) max_match = std::max(max_match, lcp[i - 1]);
            if (i < n - 1) max_match = std::max(max_match, lcp[i]);
            if (sa[i] + max_match < n) {
                ans = std::min(ans, max_match + 1);
            }
        }

        return ans;
    }
};