#pragma GCC optimize("O3,unroll-loops")
#include <vector>

class Solution {
public:
    int uniquePaths(std::vector<std::vector<int>>& grid) {
        int m = grid.size();
        if (m == 0) return 0;
        int n = grid[0].size();
        if (m == 1 && n == 1) return 1;

        std::vector<std::vector<int>> tr(m, std::vector<int>(n, -1));
        std::vector<std::vector<int>> td(m, std::vector<int>(n, -1));

        for (int r = m - 1; r >= 0; --r) {
            for (int c = n - 1; c >= 0; --c) {
                if (r == m - 1 && c == n - 1) {
                    tr[r][c] = r * n + c;
                    td[r][c] = r * n + c;
                } else if (grid[r][c] == 0) {
                    tr[r][c] = r * n + c;
                    td[r][c] = r * n + c;
                } else {
                    if (r + 1 < m) tr[r][c] = td[r + 1][c];
                    if (c + 1 < n) td[r][c] = tr[r][c + 1];
                }
            }
        }

        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
        dp[0][0] = 1;
        int MOD = 1e9 + 7;

        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (dp[r][c] == 0) continue;
                if (r == m - 1 && c == n - 1) continue;

                if (c + 1 < n) {
                    int t = tr[r][c + 1];
                    if (t != -1) {
                        int tr_r = t / n;
                        int tr_c = t % n;
                        dp[tr_r][tr_c] = (dp[tr_r][tr_c] + dp[r][c]) % MOD;
                    }
                }
                if (r + 1 < m) {
                    int t = td[r + 1][c];
                    if (t != -1) {
                        int td_r = t / n;
                        int td_c = t % n;
                        dp[td_r][td_c] = (dp[td_r][td_c] + dp[r][c]) % MOD;
                    }
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};