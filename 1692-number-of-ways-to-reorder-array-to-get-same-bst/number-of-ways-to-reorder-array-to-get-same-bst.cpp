#include <vector>

class Solution {
    long long mod = 1e9 + 7;
    std::vector<std::vector<long long>> table;
    
    long long dfs(std::vector<int>& nums) {
        int m = nums.size();
        if (m <= 2) {
            return 1;
        }
        
        std::vector<int> left, right;
        int root = nums[0];
        
        for (int i = 1; i < m; ++i) {
            if (nums[i] < root) {
                left.push_back(nums[i]);
            } else {
                right.push_back(nums[i]);
            }
        }
        
        long long left_ways = dfs(left) % mod;
        long long right_ways = dfs(right) % mod;
        
        int left_size = left.size();
        int right_size = right.size();
        
        long long current_ways = table[left_size + right_size][left_size];
        
        return (((left_ways * right_ways) % mod) * current_ways) % mod;
    }
    
public:
    int numOfWays(std::vector<int>& nums) {
        int n = nums.size();
        table.assign(n + 1, std::vector<long long>(n + 1, 0));
        
        // Pascal's Triangle for combinations nCr
        for (int i = 0; i <= n; ++i) {
            table[i][0] = 1;
            table[i][i] = 1;
            for (int j = 1; j < i; ++j) {
                table[i][j] = (table[i - 1][j - 1] + table[i - 1][j]) % mod;
            }
        }
        
        long long total_ways = dfs(nums);
        
        // Original array wale way ko subtract karna hai, isliye -1
        return (total_ways - 1 + mod) % mod;
    }
};