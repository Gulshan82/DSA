#include <vector>

class Solution {
    void dfs(std::vector<std::vector<int>>& grid, int i, int j, int m, int n, long long& current_sum) {
        if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == 0) {
            return;
        }
        
        current_sum += grid[i][j];
        grid[i][j] = 0; 
        
        dfs(grid, i + 1, j, m, n, current_sum);
        dfs(grid, i - 1, j, m, n, current_sum);
        dfs(grid, i, j + 1, m, n, current_sum);
        dfs(grid, i, j - 1, m, n, current_sum);
    }
    
public:
    int countIslands(std::vector<std::vector<int>>& grid, int k) {
        int m = grid.size();
        if (m == 0) return 0;
        int n = grid[0].size();
        
        int count = 0;
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] > 0) {
                    long long current_sum = 0;
                    dfs(grid, i, j, m, n, current_sum);
                    
                    if (current_sum % k == 0) {
                        count++;
                    }
                }
            }
        }
        
        return count;
    }
};