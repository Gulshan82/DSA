#include <vector>
#include <algorithm>

class Solution {
    bool isCyclic(const std::vector<int>& nums, int startA, const std::vector<int>& sorted_nums, int startB, int k) {
        std::vector<int> lps(k, 0);
        for (int i = 1, len = 0; i < k; ) {
            if (nums[startA + i] == nums[startA + len]) {
                lps[i++] = ++len;
            } else {
                if (len != 0) len = lps[len - 1];
                else lps[i++] = 0;
            }
        }
        for (int i = 0, j = 0; i < 2 * k; ) {
            int txt_i = i < k ? sorted_nums[startB + i] : sorted_nums[startB + i - k];
            if (nums[startA + j] == txt_i) {
                i++; j++;
            }
            if (j == k) return true;
            else if (i < 2 * k && nums[startA + j] != (i < k ? sorted_nums[startB + i] : sorted_nums[startB + i - k])) {
                if (j != 0) j = lps[j - 1];
                else i++;
            }
        }
        return false;
    }

public:
    int sortableIntegers(std::vector<int>& nums) {
        int n = nums.size();
        std::vector<int> sorted_nums = nums;
        std::sort(sorted_nums.begin(), sorted_nums.end());
        
        int total_sum = 0;
        
        for (int k = 1; k <= n; ++k) {
            if (n % k != 0) continue;
            bool ok = true;
            for (int i = 0; i < n; i += k) {
                if (!isCyclic(nums, i, sorted_nums, i, k)) {
                    ok = false;
                    break;
                }
            }
            if (ok) total_sum += k;
        }
        
        return total_sum;
    }
};