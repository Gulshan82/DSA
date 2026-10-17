#include <vector>
#include <algorithm>

class Solution {
public:
    int minSwaps(std::vector<int>& nums) {
        int n = nums.size();
        std::vector<std::pair<int, int>> arr(n);
        
        for (int i = 0; i < n; ++i) {
            arr[i] = {nums[i], i};
        }

        auto get_digit_sum = [](int num) {
            int sum = 0;
            while (num > 0) {
                sum += num % 10;
                num /= 10;
            }
            return sum;
        };

        // Custom sort based on digit sum, then by value
        std::sort(arr.begin(), arr.end(), [&](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            int sum_a = get_digit_sum(a.first);
            int sum_b = get_digit_sum(b.first);
            if (sum_a != sum_b) {
                return sum_a < sum_b;
            }
            return a.first < b.first;
        });

        int swaps = 0;
        std::vector<bool> visited(n, false);
        
        // Find cycles to count minimum swaps
        for (int i = 0; i < n; ++i) {
            if (visited[i] || arr[i].second == i) {
                continue;
            }
            
            int cycle_size = 0;
            int j = i;
            
            while (!visited[j]) {
                visited[j] = true;
                j = arr[j].second;
                cycle_size++;
            }
            
            if (cycle_size > 0) {
                swaps += (cycle_size - 1);
            }
        }
        
        return swaps;
    }
};