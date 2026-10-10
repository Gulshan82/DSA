#include <vector>
#include <cmath>
#include <algorithm>

class Solution {
public:
    long long minSumSquareDiff(std::vector<int>& nums1, std::vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        std::vector<int> diff_counts(100001, 0);
        long long k = (long long)k1 + k2;
        long long sum_diffs = 0;
        
        // Calculate absolute differences and their frequencies
        for (int i = 0; i < n; ++i) {
            int diff = std::abs(nums1[i] - nums2[i]);
            diff_counts[diff]++;
            sum_diffs += diff;
        }
        
        // Agar total difference operations (k) se chota ya barabar hai, toh answer 0 hoga
        if (sum_diffs <= k) {
            return 0;
        }
        
        // Badi differences ko pehle reduce karte hain taaki square sum minimize ho sake
        for (int i = 100000; i > 0 && k > 0; --i) {
            if (diff_counts[i] > 0) {
                long long reduce_count = std::min(k, (long long)diff_counts[i]);
                diff_counts[i] -= reduce_count;
                diff_counts[i - 1] += reduce_count;
                k -= reduce_count;
            }
        }
        
        // Final sum of squared differences calculate karna
        long long ans = 0;
        for (long long i = 1; i <= 100000; ++i) {
            if (diff_counts[i] > 0) {
                ans += (long long)diff_counts[i] * i * i;
            }
        }
        
        return ans;
    }
};