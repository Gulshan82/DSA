#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution {
    struct LastTwo {
        int first = -1;
        int second = -1;
        void add(int idx) {
            if (first == idx) return;
            second = first;
            first = idx;
        }
    };

public:
    int maxSubarray(std::vector<int>& nums) {
        int n = nums.size();
        std::unordered_map<long long, LastTwo> pos;
        int max_len = 0;
        int max_invalid_L = -1;

        auto get_latest_distinct = [&](long long target, int avoid) {
            auto it = pos.find(target);
            if (it == pos.end()) return -1;
            if (it->second.first != avoid) return it->second.first;
            return it->second.second;
        };

        for (int R = 0; R < n; ++R) {
            for (int i = R - 1; i > max_invalid_L; --i) {
                long long target1 = (long long)nums[R] - nums[i];
                int j1 = get_latest_distinct(target1, i);
                if (j1 != -1) max_invalid_L = std::max(max_invalid_L, std::min(i, j1));

                long long target2 = (long long)nums[R] + nums[i];
                int j2 = get_latest_distinct(target2, i);
                if (j2 != -1) max_invalid_L = std::max(max_invalid_L, std::min(i, j2));

                long long target3 = (long long)nums[i] - nums[R];
                int j3 = get_latest_distinct(target3, i);
                if (j3 != -1) max_invalid_L = std::max(max_invalid_L, std::min(i, j3));
            }
            pos[nums[R]].add(R);
            max_len = std::max(max_len, R - max_invalid_L);
        }
        return max_len;
    }
};