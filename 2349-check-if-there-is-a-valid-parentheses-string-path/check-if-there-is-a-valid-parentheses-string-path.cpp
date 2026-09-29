#include <vector>

class Solution {
public:
    bool hasValidPath(std::vector<std::vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        if ((m + n - 1) % 2 != 0 || grid[0][0] == ')' || grid[m - 1][n - 1] == '(') {
            return false;
        }
        
        int max_open = (m + n) / 2;
        std::vector<std::vector<std::vector<int>>> memo(m, std::vector<std::vector<int>>(n, std::vector<int>(max_open + 1, -1)));
        
        return dfs(grid, 0, 0, 0, memo, max_open);
    }
    
private:
    bool dfs(const std::vector<std::vector<char>>& grid, int r, int c, int open, std::vector<std::vector<std::vector<int>>>& memo, int max_open) {
        open += (grid[r][c] == '(' ? 1 : -1);
        
        if (open < 0 || open > max_open) {
            return false;
        }
        
        int m = grid.size();
        int n = grid[0].size();
        
        if (r == m - 1 && c == n - 1) {
            return open == 0;
        }
        
        if (memo[r][c][open] != -1) {
            return memo[r][c][open];
        }
        
        bool isValid = false;
        if (r + 1 < m) {
            isValid = isValid || dfs(grid, r + 1, c, open, memo, max_open);
        }
        if (!isValid && c + 1 < n) {
            isValid = isValid || dfs(grid, r, c + 1, open, memo, max_open);
        }
        
        return memo[r][c][open] = isValid;
    }
};